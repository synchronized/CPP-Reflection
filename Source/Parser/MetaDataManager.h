/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** MetaDataManager.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Parser/Cursor.h"

class ReflectionParser;

class MetaDataManager
{
public:
    MetaDataManager(const Cursor &cursor);

    std::string GetProperty(const std::string &key) const;
    bool GetFlag(const std::string &key) const;

    std::string GetNativeString(const std::string &key) const;

    void CompileTemplateData(
        TemplateData &data, 
        ReflectionParser *context
    ) const;

public:
    typedef std::pair<std::string, std::string> Property;

    std::unordered_map<std::string, std::string> m_properties;

    std::vector<Property> extractProperties(const Cursor &cursor) const;
};