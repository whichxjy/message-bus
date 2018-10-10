# Message Bus

---

该项目是一个使用C++实现的消息总线库。

## 消息总线

消息总线（Message Bus）提供了一种对象之间的交流方式。在消息总线中，对象只通过消息联系，而不必有直接的依赖或关联。这种统一管理的方式能极大地降低对象之间的耦合性，同时提高程序的可维护性。

参考：[①消息总线的优点][1]  [②消息总线和消息队列的异同][2]

![Message Bus][3]

*（图片来源：参考②）*

---

## 发布/订阅模式

该消息总线可用于实现发布/订阅模式。

发布/订阅模式（Publish–subscribe pattern）包含三个角色：主题（Topic），发布者（Publisher），订阅者（Subscriber）。发布者发送到Topic的消息，只有订阅了Topic的订阅者才会收到消息。每个系统可以有多个发布者，每个消息也可以有多个消费者（也即订阅者）。发布者和订阅者之间有时间上的依赖性：针对某个主题（Topic）的订阅者，它必须创建一个订阅者之后，才能消费发布者的消息。

参考：[①维基百科的解释][4]  [②发布/订阅模式在Redis中的运用][5]  [③观察者模式 vs 发布/订阅模式][6]

![Pub/Sub pattern][7]

*（图片来源：参考③）*








[延伸：从人类社会的视角分析消息总线][8]


  [1]: https://stackoverflow.com/questions/3987391/why-people-use-message-event-buses-in-their-code
  [2]: https://ardalis.com/bus-or-queue
  [3]: https://github.com/whichxjy/MessageBus/blob/master/images/Message-Bus.png
  [4]: https://en.wikipedia.org/wiki/Publish%E2%80%93subscribe_pattern
  [5]: https://github.com/ServiceStack/ServiceStack.Redis/wiki/RedisPubSub
  [6]: https://hackernoon.com/observer-vs-pub-sub-pattern-50d3b27f838c
  [7]: https://github.com/whichxjy/MessageBus/blob/master/images/PubSub.gif
  [8]: https://www.youtube.com/watch?v=hzKfabh8a68
