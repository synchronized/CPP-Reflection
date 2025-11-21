/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** FieldGetter.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Runtime/FieldGetterBase.h"

namespace ursine
{
    namespace meta
    {
        template<typename ClassType, typename FieldType, bool IsMethod>
        class FieldGetter : public FieldGetterBase
        {
        public:
            Variant GetValue(const Variant &obj) override;
            Variant GetValueReference(const Variant &obj) override;
        };
    }
}

#include "Runtime/Impl/FieldGetter.hpp"