#pragma once

#include <Runtime/Meta.h>

enum class Meta(Enable) SliderType
{
    Horizontal,
    Vertical
};

struct Meta(Enable) Slider : ursine::meta::MetaProperty
{
    META_OBJECT;

    SliderType type;

    Slider(SliderType type)
        : type(type) { }
};

struct Meta(Enable) Range : ursine::meta::MetaProperty
{
    META_OBJECT;

    float min, max;

    Range(float min, float max)
        : min(min)
        , max(max) { }
};