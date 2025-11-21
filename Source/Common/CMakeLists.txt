
file(GLOB_RECURSE HEADER_FILES *.h *.hpp)
file(GLOB_RECURSE SOURCE_FILES *.cpp)

# header files are superflous, but some IDEs (Visual Studio) don't include
# them in the solution explorer without them being added to the list of sources
set(TARGET_NAME MetaCommon)
add_library(${TARGET_NAME} INTERFACE
    ${HEADER_FILES} 
    ${SOURCE_FILES}
)

target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(${TARGET_NAME} INTERFACE fmt::fmt-header-only)

target_compile_options(${TARGET_NAME} INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>
        $<$<CXX_COMPILER_ID:MSVC>:/Zc:preprocessor>
        )

set_target_properties(${TARGET_NAME} PROPERTIES
        CXX_STANDARD 20
        DEBUG_POSTFIX ${CPP_REFLECTION_DEBUG_POSTFIX}
        FOLDER "CppReflection/Core"
        )
