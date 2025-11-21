/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** MetaContainer.cpp
** --------------------------------------------------------------------------*/

#include "Runtime/Precompiled.h"

#include "Runtime/MetaContainer.h"
#include "Runtime/MetaManager.h"

namespace ursine
{
    namespace meta
    {
        const MetaManager &MetaContainer::GetMeta(void) const
        {
            return m_meta;
        }
    }
}