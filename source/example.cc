/*****************************
 *                           *
 *       Just for test       *
 *                           *
 *****************************/

#include "MessageBus.hpp"

using std::string;
using std::cout;
using std::endl;

/*****************************************
 *                                       *
 *       Publish-subscribe pattern       *
 *                                       *
 *****************************************/

MessageBus MsgBus;
const string TopicA = "Pink Floyd";
const string TopicB = "Gorillaz";
const string CallBackTopic = "Get Message";

class Publisher {
public:
	Publisher() {
		MsgBus.AddMsg([this](const string& callBackMsg){ GetCallBack(callBackMsg); }, CallBackTopic);
	}

	void SendMsg(const string& topic) {
		//Publish
		if (topic == TopicA)
			MsgBus.SendMsg<void, const string&>("Another Brick In The Wall", TopicA);
		else if (topic == TopicB)
			MsgBus.SendMsg<void, const string&>("Tomorrow Comes Today", TopicB);
	}

	void GetCallBack(const string& callBackMsg) {
		cout << callBackMsg << endl;
	}
};

class Subscriber {
private:
	string myName;

public:
	Subscriber(const string& name) {
		myName = name;
	}

	void Subscribe(const string& topic = "") {
		MsgBus.AddMsg([this](const string& song){ GetMsg(song); }, topic);
	}

	void GetMsg(const string& song) {
		//Get Message
		cout << myName << " get message: " << song << endl;
		//Call back
		MsgBus.SendMsg<void, const string&>("Nice song!", CallBackTopic);
	}
};


int main() {
	Publisher pub;
	Subscriber subA("SubscriberA");
	Subscriber subB("SubscriberB");

	subA.Subscribe(TopicA);
	subA.Subscribe(TopicB);

	subB.Subscribe(TopicA);
	subB.Subscribe(TopicB);

	pub.SendMsg(TopicA);
	pub.SendMsg(TopicB);

	return 0;
}


