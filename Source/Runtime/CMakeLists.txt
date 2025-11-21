
set(HEADER_FILES
    VariantPolicy.h
    Argument.h
    ArgumentConfig.h
    Array.h
    ArrayVariantContainer.h
    ArrayWrapper.h
    ArrayWrapperBase.h
    ArrayWrapperContainer.h
    Constructor.h
    ConstructorInvoker.h
    ConstructorInvokerBase.h
    Destructor.h
    DestructorInvoker.h
    DestructorInvokerBase.h
    Enum.h
    EnumBase.h
    EnumContainer.h
    Field.h
    FieldGetter.h
    FieldGetterBase.h
    FieldSetter.h
    FieldSetterBase.h
    Function.h
    FunctionInvoker.h
    FunctionInvokerBase.h
    Global.h
    GlobalGetter.h
    GlobalGetterBase.h
    GlobalSetter.h
    GlobalSetterBase.h
    Invokable.h
    InvokableConfig.h
    Macros.h
    Meta.h
    MetaContainer.h
    MetaManager.h
    MetaProperty.h
    MetaTraits.h
    Method.h
    MethodInvoker.h
    MethodInvokerBase.h
    Object.h
    ObjectWrapper.h
    Precompiled.h
    ReflectionDatabase.h
    ReflectionModule.h
    RuntimeMetaProperties.h
    Type.h
    TypeCreator.h
    TypeConfig.h
    TypeData.h
    TypeInfo.h
    TypeID.h
    Variant.h
    VariantBase.h
    VariantContainer.h
    Impl/Array.hpp
    Impl/EnumContainer.hpp
    Impl/FieldGetter.hpp
    Impl/FieldSetter.hpp
    Impl/Function.hpp
    Impl/FunctionInvoker.hpp
    Impl/GlobalGetter.hpp
    Impl/GlobalSetter.hpp
    Impl/Invokable.hpp
    Impl/MetaManager.hpp
    Impl/MetaProperty.hpp
    Impl/Method.hpp
    Impl/MethodInvoker.hpp
    Impl/ReflectionDatabase.hpp
    Impl/Type.hpp
    Impl/TypeCreator.hpp
    Impl/TypeData.hpp
    Impl/TypeInfo.hpp
    Impl/TypeUnpacker.hpp
    Impl/Variant.hpp
    Impl/VariantContainer.hpp
    Impl/VariantContainerStandardTypes.hpp
    Impl/VoidFunctionInvoker.hpp
    Impl/VoidMethodInvoker.hpp
    Impl/Argument.hpp
    Impl/ArrayVariantContainer.hpp
    Impl/ArrayWrapper.hpp
    Impl/ArrayWrapperContainer.hpp
    Impl/Constructor.hpp
    Impl/ConstructorInvoker.hpp
    Impl/DestructorInvoker.hpp
)

set(SOURCE_FILES
    VariantContainer.cpp
    Argument.cpp
    ArrayWrapper.cpp
    Constructor.cpp
    Destructor.cpp
    Enum.cpp
    EnumBase.cpp
    Field.cpp
    Function.cpp
    Global.cpp
    Invokable.cpp
    MetaContainer.cpp
    MetaManager.cpp
    Method.cpp
    ObjectWrapper.cpp
    Precompiled.cpp
    ReflectionDatabase.cpp
    ReflectionModule.cpp
    Type.cpp
    TypeCreator.cpp
    TypeData.cpp
    Variant.cpp
    VariantBase.cpp
)

# header files are superflous, but some IDEs (Visual Studio) don't include
# them in the solution explorer without them being added to the list of sources
set(TARGET_NAME MetaRuntime)
add_library(${TARGET_NAME} STATIC 
    ${HEADER_FILES} 
    ${SOURCE_FILES}
)

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(${TARGET_NAME} PUBLIC MetaCommon)
target_link_libraries(${TARGET_NAME} PRIVATE json11)
target_link_libraries(${TARGET_NAME} PRIVATE mustache)

set_compiler_warnings(${TARGET_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES
        CXX_STANDARD 20
        DEBUG_POSTFIX ${CPP_REFLECTION_DEBUG_POSTFIX}
        FOLDER "CppReflection/Core"
        )

if (USE_PCH)
    target_precompile_headers(${TARGET_NAME} PRIVATE "Precompiled.h")
endif()
