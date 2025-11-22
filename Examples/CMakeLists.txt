
project(MetaTests CXX)

include(MetaParser)

include_directories(${META_RUNTIME_INCLUDE_DIRS})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

set(TEST_META_SOURCE_ROOT "${CMAKE_CURRENT_LIST_DIR}")
set(TEST_META_GENERATED_DIR "generated")

set(TEST_REFLECTION_HEADER TestReflection.h)
set(TEST_MODULE_HEADER TestReflectionModule.h)
set(TEST_MODULE_TARGET TestModule)

set(TEST_HEADERS TestProperties.h TestTypes.h)

set(META_MODULE_SOURCE_NAME "Module.${PREBUILD_META_TARGET}.Generated.cpp")

message("META_MODULE_SOURCE_NAME: ${META_MODULE_SOURCE_NAME}")
message("META_GENERATED_FILES: ${META_GENERATED_FILES}")

file(GLOB_RECURSE MODULE_FILES ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
message("MODULE_FILES: ${MODULE_FILES}")


add_library(${TEST_MODULE_TARGET} STATIC ${MODULE_FILES})
target_include_directories(${TEST_MODULE_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${TEST_MODULE_TARGET} MetaRuntime)
target_link_libraries(${TEST_MODULE_TARGET} json11)

set_compiler_warnings(${TEST_MODULE_TARGET})

set_target_properties(${TEST_MODULE_TARGET} PROPERTIES 
        FOLDER "CppReflection/Examples")

macro (add_meta_test TARGET SOURCES)
    add_executable(${TARGET} 
        ${TEST_HEADERS} 
        ${SOURCES}
    )
    target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

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
    SOURCE_FILE ${TEST_REFLECTION_HEADER}
    MODULE_HEADER ${TEST_MODULE_HEADER}
    MODULE_SOURCE_FILE_NAME ${META_MODULE_SOURCE_NAME}
    GENERATED_DIR ${TEST_META_GENERATED_DIR}
    PARSER_EXECUTABLE "$<TARGET_FILE:MetaParser>"
    TEMPLATE_DIR "${CPP_REFLECTION_TEMPLATE_DIR}"
)
