cmake_minimum_required(VERSION 3.18)

project(CPP-REFLECTION CXX)

option(CPP_REF_BUILD_EXAMPLES "Build the examples of serdepp" OFF)

if (PROJECT_IS_TOP_LEVEL)
    set(CPP_REF_BUILD_EXAMPLES ON)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/Source/CMake")

set(CPP_REFLECTION_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CPP_REFLECTION_SOURCE_DIR ${CPP_REFLECTION_ROOT_DIR}/Source)
set(CPP_REFLECTION_RESOURCES_DIR ${CPP_REFLECTION_ROOT_DIR}/Resources)
set(CPP_REFLECTION_TEMPLATE_DIR ${CPP_REFLECTION_RESOURCES_DIR}/Templates)

include(utility)
include(config)

find_package(LLVM REQUIRED)

add_subdirectory(3rd)

add_subdirectory(Source/Common)
add_subdirectory(Source/Runtime)
add_subdirectory(Source/Parser)

if(CPP_REF_BUILD_EXAMPLES)
    add_subdirectory(Examples)
endif()