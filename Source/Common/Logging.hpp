/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Logging.hpp
** --------------------------------------------------------------------------*/

#pragma once

#include <format>
#include <iostream>

#include <fmt/format.h>

namespace ursine
{
    namespace logging
    {
        template<typename... Args>
        void Assert(
            const std::string &file,
            const std::string &function,
            unsigned line,
            const char *format_str,
            const Args&... args
        )
        {
            std::cerr << "----- Assertion Failed -----" << std::endl
                      << "----------------------------" << std::endl;

            std::cerr << fmt::format(fmt::runtime(format_str), args...);

            std::cerr << std::endl;
            std::cerr << "----------------------------" << std::endl;
            std::cerr << "file: " << file << std::endl;
            std::cerr << "function: " << function << std::endl;
            std::cerr << "line: " << line << std::endl;
            std::cerr << "----------------------------" << std::endl;
            std::cerr << std::endl;

            std::abort( );
        }
    }
}