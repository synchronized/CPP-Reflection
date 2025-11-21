/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Main.cpp
** --------------------------------------------------------------------------*/

#include "Parser/Precompiled.h"

#include "Parser/ReflectionOptions.h"
#include "Parser/ReflectionParser.h"

#include "Parser/Switches.h"

#include <argparse/argparse.hpp>

#include <chrono>
#include <fstream>

void parse(ReflectionOptions& options);

int main(int argc, char *argv[])
{
    auto start = std::chrono::system_clock::now( );

    // path to the executable
    auto exeDir = fs::path( argv[ 0 ] ).parent_path( );

    // set the working directory to the executable directory
    if (!exeDir.empty( ))
        fs::current_path( exeDir );

    argparse::ArgumentParser program("Ursine Meta Parser");

    ReflectionOptions options;

    program.add_argument("--target-name")
        .help("Input target project name.")
        .store_into(options.targetName);
    program.add_argument("--source-root")
        .help("Root source directory that is shared by all header files.")
        .store_into(options.sourceRoot);
    program.add_argument("--in-source")
        .help("Source file (header) to compile reflection data from.")
        .store_into(options.inputSourceFile);
    program.add_argument("--module-header")
        .help("Header file that declares this reflection module.")
        .store_into(options.moduleHeaderFile);
    program.add_argument("--out-source")
        .help("Output generated C++ module source file.")
        .store_into(options.outputModuleSource);
    program.add_argument("--out-dir")
        .help("Output directory for generated C++ module file, header/source files.")
        .store_into(options.outputModuleFileDirectory);
    program.add_argument("--pch")
        .help("Optional name of the precompiled header file for the project.")
        .store_into(options.precompiledHeader);
    program.add_argument("--includes")
        .help("Optional file that includes the include directories for this target.")
        .store_into(options.includesFile);
    program.add_argument("--defines", "-D")
        .help("Optional list of definitions to include for the compiler.")
        .store_into(options.definesList);
    program.add_argument("--template-dir")
        .help("Directory that contains the mustache templates.")
        .store_into(options.templateDirectory);
    program.add_argument("--force-rebuild")
        .help("Whether or not to ignore cache and write the header / source files.")
        .store_into(options.forceRebuild);
    program.add_argument("--display-diagnostics")
        .help("Whether or not to display diagnostics from clang.")
        .store_into(options.displayDiagnostics);

    // parse command line
    try 
    {

        program.parse_args(argc, argv);

        parse(options);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << program;
        utils::FatalError( e.what( ) );
    }
    catch (...) 
    {
        utils::FatalError( "Unhandled exception occurred!" );
    }

    auto duration = std::chrono::system_clock::now( ) - start;

    std::cout << "Completed in " 
              << std::chrono::duration_cast<std::chrono::milliseconds>( duration ).count( ) 
              << "ms" << std::endl;

    return EXIT_SUCCESS;
}

void parse(ReflectionOptions &options)
{
    // default arguments
    options.arguments =
    { {
        "-x",
        "c++",
        "-std=c++17",
        "-D__REFLECTION_PARSER__",
        "-Wno-pragma-once-outside-header"
    } };

    if (fs::exists(options.includesFile)) 
    {
        std::ifstream includesFile( options.includesFile );

        std::string include;

        while (std::getline( includesFile, include ))
            options.arguments.emplace_back( "-I"+ include );
    }

    for (auto &define : options.definesList)
    {
        options.arguments.emplace_back( "-D"+ define );
    }

    std::cout << std::endl;
    std::cout << "Parsing reflection data for target \"" 
              << options.targetName << "\"" 
              << std::endl;

    ReflectionParser parser( options );

    parser.Parse( );
    parser.dump();

    try
    {
        parser.GenerateFiles( );
    }
    catch (std::exception &e)
    {
        utils::FatalError( e.what( ) );
    }
}