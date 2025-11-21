/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Field.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Runtime/MetaContainer.h"

#include "Runtime/Variant.h"

#include "Runtime/FieldGetter.h"
#include "Runtime/FieldSetter.h"

namespace ursine
{
    namespace meta
    {
        class Field : public MetaContainer
        {
        public:
            static bool SetValue(Variant &instance, const Variant &value, const Method &setter);

            Field(void);

            Field(
                const std::string &name, 
                Type type, 
                Type classType, 
                FieldGetterBase *getter, 
                FieldSetterBase *setter
            );

            static const Field &Invalid(void);

            bool IsValid(void) const;
            bool IsReadOnly(void) const;

            Type GetType(void) const;
            Type GetClassType(void) const;

            const std::string &GetName(void) const;

            Variant GetValue(const Variant &instance) const;
            Variant GetValueReference(const Variant &instance) const;

            bool SetValue(Variant &instance, const Variant &value) const;
            
        private:
            friend struct TypeData;

        public:
            Type m_type;
            Type m_classType;

            std::string m_name;

            std::shared_ptr<FieldGetterBase> m_getter;
            std::shared_ptr<FieldSetterBase> m_setter;
        };
    }
}