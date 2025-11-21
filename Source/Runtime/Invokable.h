/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Invokable.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Runtime/InvokableConfig.h"
#include "Runtime/ArgumentConfig.h"

#include <vector>

namespace ursine
{
    namespace meta
    {
        class Type;

        class Invokable
        {
        public:
            Invokable(const std::string &name = "INVALID");

            template<typename ...Types>
            static InvokableSignature CreateSignature(void);

            const InvokableSignature &GetSignature(void) const;

            const std::string &GetName(void) const;

        protected:
            std::string m_name;

            InvokableSignature m_signature;
        };
    }
}

#include "Runtime/Impl/Invokable.hpp"