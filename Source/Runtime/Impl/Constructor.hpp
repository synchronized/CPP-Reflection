/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Constructor.hpp
** --------------------------------------------------------------------------*/

#pragma once

#include "Runtime/Variant.h"
#include "Runtime/Argument.h"

namespace ursine
{
    namespace meta
    {
        template<typename ...Args>
        Variant Constructor::Invoke(Args &&...args) const
        {
            ArgumentList arguments { std::forward<Args>( args )... };

            return InvokeVariadic( arguments );
        }
    }
}
