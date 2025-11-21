/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** FunctionInvokerBase.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Runtime/InvokableConfig.h"
#include "Runtime/ArgumentConfig.h"

namespace ursine
{
    namespace meta
    {
        class Variant;

        class FunctionInvokerBase
        {
        public:
            virtual ~FunctionInvokerBase(void) { }

            virtual Variant Invoke(const ArgumentList &arguments) = 0;
        };
    }
}