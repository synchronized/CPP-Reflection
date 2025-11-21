/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** RuntimeMetaProperties.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Runtime/MetaProperty.h"
#include "Runtime/Type.h"

/** @brief Ensures associative enum values are serialized as their literal value.
 */
class SerializeAsNumber : public ursine::meta::MetaProperty
{
    META_OBJECT;
};