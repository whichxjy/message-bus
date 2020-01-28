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
const std::string RESPOND_TOPIC = "Respond";

class Publisher {
public:
    Publisher() {
        MESSAGE_BUS.create(RESPOND_TOPIC, [this] (const std::string& response) {
            getResponse(response);
        });
    }

    void publish(const std::string& topic) {
        if (topic == TOPIC_A) {
            MESSAGE_BUS.push<void, const std::string&>(TOPIC_A, "Another Brick In The Wall");
        }
        else if (topic == TOPIC_B) {
            MESSAGE_BUS.push<void, const std::string&>(TOPIC_B, "Tomorrow Comes Today");
        }
    }

private:
    void getResponse(const std::string& response) {
        std::cout << "Publisher gets response: " << response << std::endl;
    }
};

class Subscriber {
public:
    Subscriber(const std::string& name) : name(name) {}

    void subscribe(const std::string& topic = "") {
        MESSAGE_BUS.create(topic, [this] (const std::string& song) {
            getMessage(song);
        });
    }

private:
    std::string name;

    void getMessage(const std::string& song) {
        std::cout << name << " gets a message: " << song << std::endl;
        MESSAGE_BUS.push<void, const std::string&>(RESPOND_TOPIC, "Nice song!");
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

    publisher.publish(TOPIC_A);
    publisher.publish(TOPIC_B);
}