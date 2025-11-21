/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Function.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Parser/LanguageTypes/LanguageType.h"
#include "Parser/LanguageTypes/Invokable.h"

class Class;

class Function 
    : public LanguageType
    , public Invokable
{
public:
    Function(
        const Cursor &cursor, 
        const Namespace &currentNamespace, 
        Class *parent = nullptr
    );

    virtual ~Function(void) { }

    bool ShouldCompile(void) const;

    TemplateData CompileTemplate(
        ReflectionParser *context
    ) const override;

public:
    Class *m_parent;

    std::string m_name;
    std::string m_qualifiedName;

    bool isAccessible(void) const;

    std::string getQualifiedSignature(void) const;
};