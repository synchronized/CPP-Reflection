#pragma once

#include <Runtime/Meta.h>
#include <Runtime/Array.h>

#include "TestProperties.h"

#include <string>
#include <vector>
#include <iostream>

enum Meta(Enable) TestEnum
{
    One,
    Two,
    Three,
    Four,
    Five,
    Eighty = 80
};

struct Meta(Enable) SoundEffect
{
    Meta(Range(0.0f, 100.0f), Slider(SliderType::Horizontal))
    float volume;

    void Load(const std::string &filename)
    {
        std::cout << "Loaded sound effect \"" << filename << "\"." << std::endl;
    }
};

struct Meta(Enable) ComplexType
{
    std::string stringValue;
    int intValue;
    float floatValue;
    double doubleValue;
    
    SoundEffect soundEffect;

    ursine::Array<int> arrayValue;

    TestEnum enumValue;

    ComplexType(void) = default;
};