/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Enum.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Parser/LanguageTypes/LanguageType.h"

#include "Parser/LanguageTypes/Global.h"

class Enum : public LanguageType
{
public:
    struct Value
    {
        Value(Enum *parent, const Cursor &cursor);

        std::string key;
        std::string value;
    };

    friend struct Value;

    Enum(const Cursor &cursor, const Namespace &currentNamespace);
    virtual ~Enum(void) { }

    bool ShouldCompile(void) const;
    
    TemplateData CompileTemplate(
        ReflectionParser *context
    ) const override;

public:
    std::string m_name;
    std::string m_displayName;
    std::string m_qualifiedName;

    std::vector<Value> m_values;

    bool isAccessible(void) const;
};