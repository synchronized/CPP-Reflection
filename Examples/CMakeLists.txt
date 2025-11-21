
project(MetaTests CXX)

include(MetaParser)

include_directories(${META_RUNTIME_INCLUDE_DIRS})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

set(TEST_META_SOURCE_ROOT "${CMAKE_CURRENT_LIST_DIR}")
set(TEST_META_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/Generated")

set(TEST_META_GENERATED_HEADERS "")
set(TEST_META_GENERATED_SOURCES "")

set(TEST_REFLECTION_HEADER TestReflection.h)
set(TEST_MODULE_HEADER TestReflectionModule.h)
set(TEST_MODULE_TARGET TestModule)

set(TEST_HEADERS TestProperties.h TestTypes.h)

meta_parser_prebuild(
    TARGET ${TEST_MODULE_TARGET}
    GENERATED_DIR ${TEST_META_GENERATED_DIR}
    SOURCE_ROOT ${TEST_META_SOURCE_ROOT}
    HEADER_FILES ${TEST_HEADERS}
    MODULE_HEADER ${TEST_MODULE_HEADER}
    OUT_MODULE_SOURCE META_MODULE_SOURCE
    OUT_GENERATED_FILES META_GENERATED_FILES
    OUT_INC TEST_META_GENERATED_HEADERS
    OUT_SRC TEST_META_GENERATED_SOURCES
)
message("META_MODULE_SOURCE : ${META_MODULE_SOURCE}")
message("META_GENERATED_FILES : ${META_GENERATED_FILES}")
message("TEST_META_GENERATED_HEADERS : ${TEST_META_GENERATED_HEADERS}")
message("TEST_META_GENERATED_SOURCES : ${TEST_META_GENERATED_SOURCES}")

add_library(${TEST_MODULE_TARGET} ${META_GENERATED_FILES})
target_include_directories(${TEST_MODULE_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${TEST_MODULE_TARGET} MetaRuntime)
target_link_libraries(${TEST_MODULE_TARGET} json11)

set_compiler_warnings(${TEST_MODULE_TARGET})

set_target_properties(${TEST_MODULE_TARGET} PROPERTIES 
        FOLDER "CppReflection/Examples")

macro (add_meta_test TARGET SOURCES)
    add_executable(${TARGET} 
        ${TEST_HEADERS} 
        ${TEST_META_GENERATED_HEADERS} 
        ${TEST_META_GENERATED_SOURCES} 
        ${SOURCES}
    )

    target_link_libraries(${TARGET} MetaRuntime ${TEST_MODULE_TARGET})
    set_target_properties(${TARGET} PROPERTIES 
            FOLDER "CppReflection/Examples")
endmacro ()

add_meta_test(MetaProperties MetaProperties.cpp)
add_meta_test(Enums Enums.cpp)
add_meta_test(FunctionsAndMethods FunctionsAndMethods.cpp)
add_meta_test(Arrays Arrays.cpp)
add_meta_test(Serialization Serialization.cpp)

meta_parser_build(
    TARGET ${TEST_MODULE_TARGET}
    SOURCE_ROOT ${TEST_META_SOURCE_ROOT}
    GENERATED_DIR ${TEST_META_GENERATED_DIR}
    GENERATED_FILES ${META_GENERATED_FILES}
    SOURCE_FILE ${TEST_REFLECTION_HEADER}
    MODULE_HEADER ${TEST_MODULE_HEADER}
    MODULE_SOURCE_FILE ${META_MODULE_SOURCE}
    HEADER_FILES ${TEST_HEADERS}
    PARSER_EXECUTABLE "$<TARGET_FILE:MetaParser>"
    TEMPLATE_DIR "${CPP_REFLECTION_TEMPLATE_DIR}"
)
