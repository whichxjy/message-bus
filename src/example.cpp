/*****************************
 *                           *
 *          Example          *
 *                           *
 *****************************/

#include "MessageBus.hpp"
#include <string>

/*****************************************
 *                                       *
 *       Publish-subscribe pattern       *
 *                                       *
 *****************************************/

MessageBus MESSAGE_BUS;
const std::string TOPIC_A = "Pink Floyd";
const std::string TOPIC_B = "Gorillaz";
const std::string RESPOND_TOPIC = "Get Message";

class Publisher {
public:
    Publisher() {
        MESSAGE_BUS.addMessage([this] (const std::string& response) {
            getResponse(response);
        }, RESPOND_TOPIC);
    }

    void sendMessage(const std::string& topic) {
        if (topic == TOPIC_A) {
            MESSAGE_BUS.sendMessage<void, const std::string&>("Another Brick In The Wall", TOPIC_A);
        }
        else if (topic == TOPIC_B) {
            MESSAGE_BUS.sendMessage<void, const std::string&>("Tomorrow Comes Today", TOPIC_B);
        }
    }

private:
    void getResponse(const std::string& response) {
        std::cout << "Publisher get response: " << response << std::endl;
    }
};

class Subscriber {
public:
    Subscriber(const std::string& name) : name(name) {}

    void subscribe(const std::string& topic = "") {
        MESSAGE_BUS.addMessage([this] (const std::string& song) {
            getMessage(song);
        }, topic);
    }

private:
    std::string name;

    void getMessage(const std::string& song) {
        std::cout << name << " get message: " << song << std::endl;
        MESSAGE_BUS.sendMessage<void, const std::string&>("Nice song!", RESPOND_TOPIC);
    }
};

int main() {
    Publisher publisher;
    Subscriber subscriberA("Subscriber A");
    Subscriber subscriberB("Subscriber B");

    subscriberA.subscribe(TOPIC_A);
    subscriberA.subscribe(TOPIC_B);

    subscriberB.subscribe(TOPIC_A);
    subscriberB.subscribe(TOPIC_B);

    publisher.sendMessage(TOPIC_A);
    publisher.sendMessage(TOPIC_B);
}