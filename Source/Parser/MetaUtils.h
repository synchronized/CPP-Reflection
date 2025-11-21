/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** MetaUtils.h
** --------------------------------------------------------------------------*/

#pragma once

#include <filesystem>
#include <vector>
#include <string>

#include <Mustache.h>

#include "Parser/Cursor.h"
#include "Parser/Namespace.h"

namespace fs = std::filesystem;

namespace utils
{
    void ToString(const CXString &str, std::string &output);

    Mustache::Data<std::string>::Type TemplateBool(bool value);

    std::string GetQualifiedName(const CursorType &type);

    std::string GetQualifiedName(
        const std::string &displayName, 
        const Namespace &currentNamespace
    );

    std::string GetQualifiedName(
        const Cursor &cursor, 
        const Namespace &currentNamespace
    );

    void LoadText(const std::string &filename, std::string &output);
    void WriteText(const std::string &filename, const std::string &text);

    fs::path MakeRelativePath(
        const fs::path &from, 
        const fs::path &to
    );

    void FatalError(const std::string &error);

    template<typename A, typename B>
    bool RangeEqual(A startA, A endA, B startB, B endB);

    /** splits str into vector of substrings, str is not changed */
    std::vector<std::string> StringSplit(std::string str, const std::string delim);

    /** joins a vector of strings into a single string */
    std::string StringJoin(const std::vector<std::string> &strs, const std::string delim);

    bool StringStartWith(const std::string& content, const std::string& start);
}

#include "Parser/MetaUtils.hpp"