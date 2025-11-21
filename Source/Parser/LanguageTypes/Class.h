/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Class.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Parser/LanguageTypes/LanguageType.h"

#include "Parser/LanguageTypes/Constructor.h"
#include "Parser/LanguageTypes/Field.h"
#include "Parser/LanguageTypes/Global.h"
#include "Parser/LanguageTypes/Method.h"
#include "Parser/LanguageTypes/Function.h"

struct BaseClass
{
    BaseClass(const Cursor &cursor);

    std::string name;
};

class Class : public LanguageType
{
    // to access m_qualifiedName
    friend class Global;
    friend class Function;
    friend class Method;
    friend class Constructor;
    friend class Field;

public:
    Class(const Cursor &cursor, const Namespace &currentNamespace);

    virtual bool ShouldCompile(void) const;

    TemplateData CompileTemplate(
        ReflectionParser *context
    ) const override;
    
public:
    std::string m_name;
    std::string m_displayName;
    std::string m_qualifiedName;

    template<typename T>
    using SharedPtrVector = std::vector<std::shared_ptr<T>>;

    SharedPtrVector<BaseClass> m_baseClasses;

    SharedPtrVector<Constructor> m_constructors;

    SharedPtrVector<Field> m_fields;
    SharedPtrVector<Global> m_staticFields;

    SharedPtrVector<Method> m_methods;
    SharedPtrVector<Function> m_staticMethods;

    bool isAccessible(void) const;
};
