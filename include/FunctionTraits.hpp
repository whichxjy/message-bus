#ifndef _FUNCTION_TRAITS_HPP_
#define _FUNCTION_TRAITS_HPP_

#include <functional>

namespace func_traits {
    // helper
    template <typename RetType, typename... Args>
    struct FunctionTraitsHelper {
        using ReturnType = RetType;
        using FunctionType = RetType(Args...);
        using FunctionWrapperType = std::function<FunctionType>;
    };

    template <typename T>
    struct FunctionTraits;

    //---------------------------------------------------------------------

    // normal function
    template <typename RetType, typename... Args>
    struct FunctionTraits<RetType(Args...)>
    : FunctionTraitsHelper<RetType, Args...> {};

    // function pointer
    template <typename RetType, typename... Args>
    struct FunctionTraits<RetType(*)(Args...)>
    : FunctionTraitsHelper<RetType, Args...> {};

    // function reference
    template <typename RetType, typename... Args>
    struct FunctionTraits<RetType(&)(Args...)>
    : FunctionTraitsHelper<RetType, Args...> {};

    //---------------------------------------------------------------------

    // pointer to member fuction
    template <typename CType, typename RetType, typename... Args>
    struct FunctionTraits<RetType(CType::*)(Args...)>
    : FunctionTraitsHelper<RetType, Args...> {
        using ClassType = CType;
    };

    // (const version) pointer to member fuction
    template <typename CType, typename RetType, typename... Args>
    struct FunctionTraits<RetType(CType::*)(Args...) const>
    : FunctionTraitsHelper<RetType, Args...> {
        using ClassType = CType;
    };

    // callable (lambda or std::function<> or bind())
    template <typename T>
    struct FunctionTraits
    : FunctionTraits<decltype(&T::operator())> {};
}

#endif