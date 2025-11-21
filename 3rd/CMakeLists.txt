
set(CPP_REFLECTION_3RD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# Find json11
if(NOT TARGET json11)
    set(JSON11_DIR ${CPP_REFLECTION_3RD_PARTY_DIR}/json11)
    add_library(json11 ${JSON11_DIR}/json11.cpp)
    target_include_directories(json11 PUBLIC ${JSON11_DIR})
    set_target_properties(json11 PROPERTIES
        FOLDER "CppReflection/3rdParty"
        )
endif()

# Find Mustache 
if(NOT TARGET mustache)
    set(MUSTACHE_DIR ${CPP_REFLECTION_3RD_PARTY_DIR}/mustache)
    add_library(mustache INTERFACE)
    target_include_directories(mustache INTERFACE ${MUSTACHE_DIR})
    set_target_properties(mustache PROPERTIES
        FOLDER "CppReflection/3rdParty"
        )
endif()

if(NOT TARGET fmt::fmt-header-only)
    set(FMT_ROOT_DIR "${CPP_REFLECTION_3RD_PARTY_DIR}/fmt-v12.1.0")
    add_library(fmt-header-only INTERFACE)
    add_library(fmt::fmt-header-only ALIAS fmt-header-only)
    target_include_directories(fmt-header-only INTERFACE ${FMT_ROOT_DIR}/include)

    if (NOT MSVC)
    # Unicode is always supported on compilers other than MSVC.
    elseif (FMT_UNICODE)
        # Unicode support requires compiling with /utf-8.
        target_compile_options(fmt-header-only INTERFACE $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:MSVC>>:/utf-8>)
    endif ()

    target_compile_definitions(fmt-header-only INTERFACE FMT_HEADER_ONLY=1)
    target_compile_features(fmt-header-only INTERFACE cxx_std_11)
    set_target_properties(fmt-header-only PROPERTIES
        FOLDER "CppReflection/3rdParty"
        )
endif()

if(NOT TARGET argparse::argparse)
    add_subdirectory(argparse-3.2)
endif()