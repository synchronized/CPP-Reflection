/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ReflectionModule.cpp
** --------------------------------------------------------------------------*/

#include "Runtime/Precompiled.h"

#include "Runtime/ReflectionModule.h"

namespace ursine
{
    namespace meta
    {
        ReflectionModule::ReflectionModule(ReflectionDatabase &db)
            : db( db ) { }
    }
}