#ifndef MESSAGE_BUS_HPP
#define MESSAGE_BUS_HPP

#include <string>
#include <map>
#include <boost/any.hpp>

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
	void AddMsg(F&& func, const std::string& topic = "");

	//Delete Message(s) in Message Bus
	template <typename RetType, typename... Args>
	void RemoveMsg(const std::string& topic = "");

	//Send message(s) without argument
	template <typename RetType>
	void SendMsg(const std::string& topic = "");

	//Send message(s) with argument(s)
	template <typename RetType, typename... Args>
	void SendMsg(Args&&... args, const std::string& topic = "");

};

#endif
