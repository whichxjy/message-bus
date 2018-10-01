#ifndef MESSAGE_BUS_HPP
#define MESSAGE_BUS_HPP

#include <string>
#include <map>
#include <boost/any.hpp>

using std::string;

class MessageBus {

private:
	std::multimap<std::string, boost::any> container;
	using Iter = std::multimap<std::string, boost::any>::iterator;
public:
	MessageBus();
	/*禁止复制*/
	MessageBus(const MessageBus&) = delete;
	MessageBus(MessageBus&&) = delete;

	/*添加消息*/
	template <typename F>
	void AddMsg(F&& func, const string& topic = "");

	/*删除消息*/
	template <typename R, typename... Args>
	void RemoveMsg(const string& topic = "");

	/*发送消息*/
	template <typename R, typename... Args>
	void SendMsg(const string& topic = "");
		


};

#endif
