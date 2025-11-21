/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Precompiled.h
** --------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <functional>
#include <filesystem>

#pragma warning(push)
#pragma warning(disable:4996)
#include <clang-c/Index.h>
#pragma warning(pop)

#include <Mustache.h>

#include "Parser/MetaUtils.h"
#include "Parser/MetaDataConfig.h"

using MustacheTemplate = Mustache::Mustache<std::string>;
using TemplateData = Mustache::Data<std::string>;

namespace fs = std::filesystem;