#ifndef FUNCTION_TRAITS_HPP
#define FUNCTION_TRAITS_HPP

#include <functional>

namespace func_traits {
	template <typename T>
	struct FunctionTraits;

	//normal function
	template <typename RetType, typename... Args>
	struct FunctionTraits<RetType(Args...)> {
		using return_type = RetType;
		using function_type = RetType(Args...);
		using function_wrapper_type = std::function<function_type>;
	};

	//function pointer
	template <typename RetType, typename... Args>
	struct FunctionTraits<RetType(*)(Args...)> : FunctionTraits<RetType(Args...)> {};

	//function wrapper
	template <typename RetType, typename... Args>
	struct FunctionTraits<std::function<RetType(Args...)>> :FunctionTraits<RetType(Args...)> {};

	//Callable


	//transform lambda to function wrapper
	template <typename Func>
	typename FunctionTraits<Func>::function_wrapper_type LambdaToFuncWrapper(const Func& lambda) {
		return static_cast<typename FunctionTraits<Func>::function_wrapper_type>(lambda);
	}
	
}


#endif


