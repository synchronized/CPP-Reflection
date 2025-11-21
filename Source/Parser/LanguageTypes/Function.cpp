/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Function.cpp
** --------------------------------------------------------------------------*/

#include <fmt/format.h>

#include "Parser/Precompiled.h"

#include "Parser/LanguageTypes/Function.h"
#include "Parser/LanguageTypes/Class.h"

Function::Function(
    const Cursor &cursor, 
    const Namespace &currentNamespace, 
    Class *parent
)
    : LanguageType( cursor, currentNamespace )
    , Invokable( cursor )
    , m_parent( parent )
    , m_name( cursor.GetSpelling( ) )
    , m_qualifiedName( utils::GetQualifiedName( cursor, currentNamespace ) )
{
        
}

bool Function::ShouldCompile(void) const
{
    return isAccessible( );
}

TemplateData Function::CompileTemplate(ReflectionParser *context) const
{
    TemplateData data { TemplateData::Type::Object };

    data[ "name" ] = m_name;
    data[ "qualifiedName" ] = m_qualifiedName;

    if (m_parent)
        data[ "parentQualifiedName" ] = m_parent->m_qualifiedName;
    
    data[ "qualifiedSignature" ] = getQualifiedSignature( );

    m_metaData.CompileTemplateData( data, context );

    return data;
}

bool Function::isAccessible(void) const
{
    if (m_parent && m_accessModifier != CX_CXXPublic)
        return false;

    return m_enabled;
}

std::string Function::getQualifiedSignature(void) const
{
    std::string argsList = utils::StringJoin( m_signature, ", " );

    return fmt::format( "{}(*)({})", m_returnType, argsList);
}