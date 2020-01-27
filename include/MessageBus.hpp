#ifndef _MESSAGE_BUS_HPP_
#define _MESSAGE_BUS_HPP_

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
    // use the synthesized default constructor
    MessageBus() = default;

    // no copy
    MessageBus(const MessageBus&) = delete;
    MessageBus(MessageBus&&) = delete;

    // no assignment
    MessageBus& operator= (const MessageBus&) = delete;
    MessageBus& operator= (MessageBus&&) = delete;

    // use the synthesized destructor
    ~MessageBus() = default;

    // add message to message bus
    template <typename F>
    void addMessage(F&& func, const std::string& topic = "") {
        using function_wrapper_type = typename FunctionTraits<F>::function_wrapper_type;
        function_wrapper_type funcWrapper = func;
        std::string tag = topic + typeid(funcWrapper).name();
        container.emplace(std::move(tag), std::forward<function_wrapper_type>(funcWrapper));
    }    

    // delete messages in Message Bus
    template <typename RetType, typename... Args>
    void removeMessage(const std::string& topic = "") {
        using function_wrapper_type = std::function<RetType(Args...)>;
        std::string removeTag = topic + typeid(function_wrapper_type).name();
        auto removeRange = container.equal_range(removeTag);
        if (removeRange.first == removeRange.second) {
            std::cout << "Message not found." << std::endl;
        }
        else {
            container.erase(removeRange.first, removeRange.second);
        }
    }

    // send messages without argument
    template <typename RetType>
    void sendMessage(const std::string& topic = "") {
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

    // send messages with arguments
    template <typename RetType, typename... Args>
    void sendMessage(Args&&... args, const std::string& topic = "") {
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