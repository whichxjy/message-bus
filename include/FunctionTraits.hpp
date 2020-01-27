#ifndef _FUNCTION_TRAITS_HPP_
#define _FUNCTION_TRAITS_HPP_

#include <functional>

namespace func_traits {
    // helper
    template <typename RetType, typename... Args>
    struct FunctionTraitsHelper {
        using return_type = RetType;
        using function_type = RetType(Args...);
        using function_wrapper_type = std::function<function_type>;
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
    template <typename ClassType, typename RetType, typename... Args>
    struct FunctionTraits<RetType(ClassType::*)(Args...)>
    : FunctionTraitsHelper<RetType, Args...> {
        using class_type = ClassType;
    };

    // (const version) pointer to member fuction
    template <typename ClassType, typename RetType, typename... Args>
    struct FunctionTraits<RetType(ClassType::*)(Args...) const>
    : FunctionTraitsHelper<RetType, Args...> {
        using class_type = ClassType;
    };
    
    // callable (lambda or std::function<> or bind())
    template <typename T>
    struct FunctionTraits 
    : FunctionTraits<decltype(&T::operator())> {};
}

#endif