/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Method.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Parser/LanguageTypes/LanguageType.h"
#include "Parser/LanguageTypes/Invokable.h"

class Class;

class Method 
    : public LanguageType
    , public Invokable
{
public:
    Method(
        const Cursor &cursor, 
        const Namespace &currentNamespace, 
        Class *parent = nullptr
    );

    virtual ~Method(void) { }

    bool ShouldCompile(void) const;
    
    TemplateData CompileTemplate(
        ReflectionParser *context
    ) const override;

public:
    bool m_isConst;

    Class *m_parent;

    std::string m_name;

    bool isAccessible(void) const;

    std::string getQualifiedSignature(void) const;
};