/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ReflectionOptions.h
** --------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <vector>

struct ReflectionOptions
{
    bool forceRebuild;
    bool displayDiagnostics;
    bool verbose;

    std::string targetName;

    std::string sourceRoot;
    std::string inputSourceFile;
    std::string moduleHeaderFile;

    std::string outputModuleSourceFileName;
    std::string outputDirectory; //输出路径

    std::string precompiledHeader;

    std::string templateDirectory;

    std::string includesFile;
    std::vector<std::string> definesList;

    std::vector<std::string> arguments;
};