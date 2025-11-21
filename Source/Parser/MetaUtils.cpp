/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** MetaUtils.cpp
** --------------------------------------------------------------------------*/

#include "Parser/Precompiled.h"

#include "Parser/MetaUtils.h"

#include <fstream>
#include <exception>
#include <system_error>

namespace utils
{
    void ToString(const CXString &str, std::string &output)
    {
        auto cstr = clang_getCString( str );

        output = cstr;

        clang_disposeString( str );
    }

    TemplateData::Type TemplateBool(bool value)
    {
        return value ? TemplateData::Type::True : TemplateData::Type::False;
    }

    std::string GetQualifiedName(const CursorType &type)
    {
        if (type.GetKind( ) != CXType_Typedef)
            return type.GetDisplayName( );

        auto declaration = type.GetDeclaration( );

        auto parent = declaration.GetLexicalParent( );

        Namespace parentNamespace;

        // walk up to the root namespace
        while (parent.GetKind( ) == CXCursor_Namespace)
        {
            parentNamespace.emplace( parentNamespace.begin( ), parent.GetDisplayName( ) );

            parent = parent.GetLexicalParent( );
        }

        // add the display name as the end of the namespace
        parentNamespace.emplace_back(
            type.GetDisplayName( )
        );

        return StringJoin( parentNamespace, "::" );
    }

    std::string GetQualifiedName(
        const std::string &displayName, 
        const Namespace &currentNamespace
    )
    {
        auto name = StringJoin( currentNamespace, "::" );

        if (!currentNamespace.empty( ))
            name += "::";

        name += displayName;

        return name;
    }

    std::string GetQualifiedName(
        const Cursor &cursor, 
        const Namespace &currentNamespace
    )
    {
        return GetQualifiedName( cursor.GetSpelling( ), currentNamespace );
    }

    void LoadText(const std::string &filename, std::string &output)
    {
        std::ifstream input( filename );

        if (!input)
        {
            std::stringstream error;

            error << "Unable to open file \"" 
                  << filename 
                  << "\" for reading." << std::endl;
            error << std::error_code(errno, std::system_category()).message();

            throw std::runtime_error( error.str( ) );
        }

        input.seekg( 0, std::ios::end );

        output.reserve(
            static_cast<std::string::size_type>( input.tellg( ) )
        );

        input.seekg( 0, std::ios::beg );

        output.assign(
            // disambiguate function declaration
            (std::istreambuf_iterator<char>( input )),
            std::istreambuf_iterator<char>( ) 
        );

        input.close( );
    }

    void WriteText(const std::string &filename, const std::string &text)
    {
        std::ofstream output( filename );

        if (!output)
        {
            std::stringstream error;

            error << "Unable to open file \"" 
                  << filename << "\" for writing." 
                  << std::endl;
            error << std::error_code(errno, std::system_category()).message();

            throw std::runtime_error( error.str( ) );
        }

        output << text;

        output.close( );
    }

    fs::path MakeRelativePath(const fs::path &from, const fs::path &to)
    {
        // Start at the root path and while they are the same then do nothing then when they first
        // diverge take the remainder of the two path and replace the entire from path with ".."
        // segments.
        auto itFrom = from.begin( );
        auto itTo = to.begin( );

        // Loop through both
        while (itFrom != from.end( ) && itTo != to.end( ) && (*itTo) == (*itFrom))
        {
            ++itTo;
            ++itFrom;
        }

        fs::path finalPath;

        while (itFrom != from.end( ))
        {
            finalPath /= "..";

            ++itFrom;
        }

        while (itTo != to.end( ))
        {
            finalPath /= *itTo;

            ++itTo;
        }

        return finalPath;
    }

    void FatalError(const std::string &error)
    {
        std::cerr << "Error: " << error << std::endl;

        exit( EXIT_FAILURE );
    }

    /** splits str into vector of substrings, str is not changed */
    std::vector<std::string> StringSplit(std::string str, const std::string delim)
    {
        std::vector<std::string> res;
        size_t pos;
        while ((pos = str.find(delim)) != std::string::npos)
        {
            res.push_back(str.substr(0, pos));
            str.erase(0, pos + delim.length());
        }
        res.push_back(str);
        return res;
    }


    /** joins a vector of strings into a single string */
    std::string StringJoin(const std::vector<std::string> &strs, const std::string delim)
    {
        if (strs.size() == 0) return "";
        std::vector<char> res;
        for (int i = 0; i < strs.size()-1; ++i)
        {
            for (auto c: strs[i]) res.push_back(c);
            for (auto c: delim) res.push_back(c);
        }
        for (auto c: strs[strs.size()-1]) res.push_back(c);
        return std::string{res.begin(), res.end()};
    }

    bool StringStartWith(const std::string& content, const std::string& start) {
        return (content.rfind(start, 0) == 0);
    }
}