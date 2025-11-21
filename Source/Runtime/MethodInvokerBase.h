/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** MethodInvokerBase.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Runtime/InvokableConfig.h"
#include "Runtime/ArgumentConfig.h"

namespace ursine
{
    namespace meta
    {
        class Variant;

        class MethodInvokerBase
        {
        public:
            virtual ~MethodInvokerBase(void) { }

            virtual Variant Invoke(Variant &obj, const ArgumentList &arguments) = 0;
        };
    }
}