#include "MessageBus.hpp"
#include "FunctionTraits.hpp"
#include <iostream>

using namespace func_traits;

//Add message to message bus
template <typename F>
void MessageBus::AddMsg(F&& func, const std::string& topic) {
	auto funcWrapper = ToFuncWrapper(std::forward<F>(func));
	using function_wrapper_type = typename FunctionTraits<F>::function_wrapper_type;
	std::string tag = topic + typeid(funcWrapper).name();
	container.emplace(std::move(tag), std::forward<function_wrapper_type>(funcWrapper));
}	

//Delete Message(s) in Message Bus
template <typename RetType, typename... Args>
void MessageBus::RemoveMsg(const std::string& topic) {
	using function_wrapper_type = std::function<RetType(Args...)>;
	std::string removeTag = topic + typeid(function_wrapper_type).name();
	auto removeRange = container.equal_range(removeTag);
	if (removeRange.first == removeRange.second)
		std::cout << "Message not found." << std::endl;
	else
		container.erase(removeRange.first, removeRange.second);
}

//Send message(s) without argument
template <typename RetType>
void MessageBus::SendMsg(const std::string& topic){
	using function_wrapper_type = std::function<RetType()>;
	std::string sendTag = topic + typeid(function_wrapper_type).name();
	auto sendRange = container.equal_range(sendTag);
		if (sendRange.first == sendRange.second) {
		std::cout << "Message not found." << std::endl;
		return;
	}
	for (Iter it = sendRange.first; it != sendRange.second; ++it) {
		function_wrapper_type funcWrapper = boost::any_cast<function_wrapper_type>(it->second);
		funcWrapper();
	}
}

//Send message(s) with argument(s)
template <typename RetType, typename... Args>
void MessageBus::SendMsg(Args&&... args, const std::string& topic){
	using function_wrapper_type = std::function<RetType(Args...)>;
	std::string sendTag = topic + typeid(function_wrapper_type).name();
	auto sendRange = container.equal_range(sendTag);
	if (sendRange.first == sendRange.second) {
		std::cout << "Message not found." << std::endl;
		return;
	}
	for (Iter it = sendRange.first; it != sendRange.second; ++it) {
		function_wrapper_type funcWrapper = boost::any_cast<function_wrapper_type>(it->second);
		funcWrapper(std::forward<Args>(args)...);
	}
}

