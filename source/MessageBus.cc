#include "MessageBus.hpp"
#include <string>

using namespace func_traits;

/*Add message to message bus*/
template <typename F>
void MessageBus::AddMsg(F&& func, const std::string& topic) {
	auto funcWrapper = ToFuncWrapper(std::forward<F>(func));
	using function_wrapper_type = typename FunctionTraits<F>::function_wrapper_type;
	std::string tag = topic + typeid(funcWrapper).name();
	container.emplace(std::move(tag), std::forward<function_wrapper_type>(funcWrapper));
}	

/*Delete Message(s) in Message Bus*/
template <typename R, typename... Args>
void RemoveMsg(const std::string& topic = "");

/*Send message(s)*/
template <typename R, typename... Args>
void SendMsg(const std::string& topic = "");

