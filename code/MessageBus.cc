#include "MessageBus.hpp"

/***********
 * 添加消息 *
 ***********
 */
template <typename F>
void MessageBus::AddMsg(F&& func, const std::string& topic) {
	

}




/*删除消息*/
template <typename R, typename... Args>
void RemoveMsg(const std::string& topic = "");

/*发送消息*/
template <typename R, typename... Args>
void SendMsg(const std::string& topic = "");

