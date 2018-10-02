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
	//MessageBus();

	/*Copy is not allowed*/
	MessageBus(const MessageBus&) = delete;
	MessageBus(MessageBus&& ) = delete;

	/*Add message to message bus*/
	template <typename F>
	void AddMsg(F&& func, const std::string& topic = "");

	/*Delete Message(s) in Message Bus*/
	template <typename R, typename... Args>
	void RemoveMsg(const std::string& topic = "");

	/*Send message(s)*/
	template <typename R, typename... Args>
	void SendMsg(const std::string& topic = "");

};

#endif
