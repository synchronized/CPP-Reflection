/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** External.cpp
** --------------------------------------------------------------------------*/

#include "Parser/Precompiled.h"

#include "Parser/LanguageTypes/External.h"

External::External(const Cursor &cursor)
    : Class( cursor, { } )
{
    
}

bool External::ShouldCompile(void) const
{
    return true;
}