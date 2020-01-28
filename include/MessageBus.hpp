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

    // create a node with a topic and a callback function
    template <typename F>
    void create(const std::string& topic, F&& func) {
        using FunctionWrapperType = typename FunctionTraits<F>::FunctionWrapperType;
        FunctionWrapperType func_wrapper = func;
        const std::string tag = topic + typeid(func_wrapper).name();
        container.emplace(std::move(tag), std::forward<FunctionWrapperType>(func_wrapper));
    }

    // remove nodes that are listening to the given topic and have the given call signature
    template <typename RetType, typename... Args>
    void remove(const std::string& topic) {
        using FunctionWrapperType = std::function<RetType(Args...)>;
        const std::string remove_tag = topic + typeid(FunctionWrapperType).name();
        auto remove_range = container.equal_range(remove_tag);
        if (remove_range.first == remove_range.second) {
            std::cout << "Node not found." << std::endl;
        }
        else {
            container.erase(remove_range.first, remove_range.second);
        }
    }

    // send messages to nodes without argument
    template <typename RetType>
    void push(const std::string& topic) {
        using FunctionWrapperType = std::function<RetType()>;
        const std::string push_tag = topic + typeid(FunctionWrapperType).name();
        auto send_range = container.equal_range(push_tag);
        if (send_range.first == send_range.second) {
            std::cout << "Node not found." << std::endl;
            return;
        }
        for (Iter it = send_range.first; it != send_range.second; ++it) {
            FunctionWrapperType func_wrapper = boost::any_cast<FunctionWrapperType>(it->second);
            func_wrapper();
        }
    }

    // send messages to nodes with arguments
    template <typename RetType, typename... Args>
    void push(const std::string& topic, Args&&... args) {
        using FunctionWrapperType = std::function<RetType(Args...)>;
        const std::string push_tag = topic + typeid(FunctionWrapperType).name();
        auto send_range = container.equal_range(push_tag);
        if (send_range.first == send_range.second) {
            std::cout << "Node not found." << std::endl;
            return;
        }
        for (Iter it = send_range.first; it != send_range.second; ++it) {
            FunctionWrapperType func_wrapper = boost::any_cast<FunctionWrapperType>(it->second);
            func_wrapper(std::forward<Args>(args)...);
        }
    }
};

#endif