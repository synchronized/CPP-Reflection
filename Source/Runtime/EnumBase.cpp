/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** EnumBase.cpp
** --------------------------------------------------------------------------*/

#include "Runtime/Precompiled.h"

#include "Runtime/EnumBase.h"

#include "Runtime/Variant.h"
#include "Runtime/Argument.h"

namespace ursine
{
    namespace meta
    {
        EnumBase::EnumBase(const std::string &name, TypeID owner)
            : m_parentType( owner )
            , m_name( name ) { }

        Type EnumBase::GetParentType(void) const
        {
            return m_parentType;
        }

        const std::string &EnumBase::GetName(void) const
        {
            return m_name;
        }
    }
}