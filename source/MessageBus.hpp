#ifndef MESSAGE_BUS_HPP
#define MESSAGE_BUS_HPP

#include "FunctionTraits.hpp"
#include <iostream>
#include <string>
#include <map>
#include <boost/any.hpp>

using namespace func_traits;

class MessageBus {
private:
	std::multimap<std::string, boost::any> container;
	using Iter = std::multimap<std::string, boost::any>::iterator;

public:
	//Use the synthesized default constructor
	MessageBus() = default;

	//No copy
	MessageBus(const MessageBus&) = delete;
	MessageBus(MessageBus&&) = delete;

	//No assignment
	MessageBus& operator= (const MessageBus&) = delete;
	MessageBus& operator= (MessageBus&&) = delete;

	//Use the synthesized destructor
	~MessageBus() = default;

	//Add message to message bus
	template <typename F>
	void AddMsg(F&& func, const std::string& topic = "") {
		using function_wrapper_type = typename FunctionTraits<F>::function_wrapper_type;
		function_wrapper_type funcWrapper = func;
		std::string tag = topic + typeid(funcWrapper).name();
		container.emplace(std::move(tag), std::forward<function_wrapper_type>(funcWrapper));
	}	

	//Delete Message(s) in Message Bus
	template <typename RetType, typename... Args>
	void RemoveMsg(const std::string& topic = "") {
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
	void SendMsg(const std::string& topic = "") {
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
	void SendMsg(Args&&... args, const std::string& topic = "") {
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

};

#endif
