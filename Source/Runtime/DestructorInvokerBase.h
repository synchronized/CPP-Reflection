/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** DestructorInvokerBase.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Runtime/InvokableConfig.h"

namespace ursine
{
    namespace meta
    {
        class Variant;

        class DestructorInvokerBase
        {
        public:
            virtual ~DestructorInvokerBase(void) { }

            virtual void Invoke(const Variant &obj) = 0;
        };
    }
}