
set(HEADER_FILES
    Cursor.h
    CursorType.h
    MetaDataConfig.h
    MetaDataManager.h
    MetaUtils.h
    MetaUtils.hpp
    Namespace.h
    Precompiled.h
    ReflectionOptions.h
    ReflectionParser.h
    ReservedTypes.h
    Switches.h
    Templates.h
    Version.h
    LanguageTypes/Class.h
    LanguageTypes/Constructor.h
    LanguageTypes/Enum.h
    LanguageTypes/External.h
    LanguageTypes/Field.h
    LanguageTypes/Function.h
    LanguageTypes/Global.h
    LanguageTypes/Invokable.h
    LanguageTypes/LanguageType.h
    LanguageTypes/Method.h
    Module/ModuleFile.h
    Tokenizer/TokenizerResult.h
    Tokenizer/TokenizerState.h
    Tokenizer/TokenType.h
    Tokenizer/Token.h
    Tokenizer/Tokenizer.h
    Tokenizer/ConstructorTokenSymbols.inl
    Tokenizer/Impl/TokenizerResult.hpp
    Tokenizer/Impl/TokenizerState.hpp
    Tokenizer/Impl/Token.hpp
    Tokenizer/Impl/Tokenizer.hpp
)

set(SOURCE_FILES
    Cursor.cpp
    CursorType.cpp
    Main.cpp
    MetaDataManager.cpp
    MetaUtils.cpp
    Precompiled.cpp
    ReflectionParser.cpp
    LanguageTypes/Class.cpp
    LanguageTypes/Constructor.cpp
    LanguageTypes/Enum.cpp
    LanguageTypes/External.cpp
    LanguageTypes/Field.cpp
    LanguageTypes/Function.cpp
    LanguageTypes/Global.cpp
    LanguageTypes/Invokable.cpp
    LanguageTypes/LanguageType.cpp
    LanguageTypes/Method.cpp
)

find_package(LLVM REQUIRED)

# add LLVM includes
set(TARGET_NAME MetaParser)
add_executable(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${TARGET_NAME} PRIVATE ${CPP_REFLECTION_SOURCE_DIR})

target_link_libraries(${TARGET_NAME} PRIVATE json11)
target_link_libraries(${TARGET_NAME} PRIVATE mustache)
target_link_libraries(${TARGET_NAME} PRIVATE fmt::fmt-header-only)
target_link_libraries(${TARGET_NAME} PRIVATE LLVM::clang)
target_link_libraries(${TARGET_NAME} PRIVATE argparse::argparse)

# header files are superflous, but some IDEs (Visual Studio) don't include
# them in the solution explorer without them being added to the list of sources

target_compile_options(${TARGET_NAME} PUBLIC
        $<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>
        $<$<CXX_COMPILER_ID:MSVC>:/Zc:preprocessor>
        )
set_compiler_warnings(${TARGET_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES
        CXX_STANDARD 20
        DEBUG_POSTFIX ${CPP_REFLECTION_DEBUG_POSTFIX}
        FOLDER "CppReflection/Core"
        )

if (USE_PCH)
    target_precompile_headers(${TARGET_NAME} PRIVATE "Precompiled.h")
endif()


# copy resources on post build
add_custom_command(TARGET MetaParser POST_BUILD
    # mustache templates directory
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CPP_REFLECTION_RESOURCES_DIR}"
        $<TARGET_FILE_DIR:MetaParser>
    # LibClang shared library
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${LIBCLANG_SHARED_LIBRARY}
        $<TARGET_FILE_DIR:MetaParser>
)

# 创建一个小的 CMake 项目来探测包含路径
function(detect_include_paths)
    # 创建一个临时目录
    set(temp_dir "${CMAKE_BINARY_DIR}/include_detect")
    file(MAKE_DIRECTORY "${temp_dir}")
    
    # 创建测试 CMakeLists.txt
    file(WRITE "${temp_dir}/main.cpp" "int main() { return 0; }")
    
    # 执行配置
    execute_process(
        #clang++ -E -Wp -v -xc++ main.cpp
        COMMAND ${CMAKE_COMMAND} -S "${temp_dir}" -B "${temp_dir}"
        OUTPUT_VARIABLE config_output
        ERROR_VARIABLE config_error
    )
    
    # 清理
    file(REMOVE_RECURSE "${temp_dir}")
    
    message("${config_output}")
    message("${config_error}")
endfunction()

#detect_include_paths()