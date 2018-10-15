# Message Bus

## 项目简介

该项目是一个使用C++实现的消息总线库。

---

 - **消息总线**

消息总线（Message Bus）提供了一种对象之间的交流方式。在消息总线中，对象只通过消息联系，而不必有直接的依赖或关联。这种统一管理的方式能极大地降低对象之间的耦合性，同时提高程序的可维护性。

参考：[①消息总线的优点][1]  [②消息总线和消息队列的异同][2]

![Message Bus][3]

*（图片来源：参考②）*

---

 - **发布/订阅模式**

该消息总线可用于实现发布/订阅模式。

发布/订阅模式（Publish–subscribe pattern）包含三个角色：主题（Topic），发布者（Publisher），订阅者（Subscriber）。发布者发送到Topic的消息，只有订阅了Topic的订阅者才会收到消息。每个系统可以有多个发布者，每个消息也可以有多个消费者（也即订阅者）。发布者和订阅者之间有时间上的依赖性：针对某个主题（Topic）的订阅者，它必须创建一个订阅者之后，才能消费发布者的消息。

参考：[①维基百科的解释][4]  [②发布/订阅模式在Redis中的运用][5]  [③观察者模式 vs 发布/订阅模式][6]

![Pub/Sub pattern][7]

*（图片来源：参考③）*

## 实现原理

 - **消息的表示**：可调用对象（函数、函数指针、lambda表达式、bind创建的对象、重载了函数调用运算符的类、function标准库类型）可以看作是一种承载了具体内容的消息类型，对象之间可通过可调用对象传递信息。在本项目中，每个消息的类型由其Topic以及泛型函数类型（std::function<R(Args)>）共同确定。
 - **消息的添加**：为了在消息总线中添加消息，我们需要传入消息的Topic以及一个泛型函数对象。当某Topic的消息发布时，调用对应的泛型函数。
 - **消息的存储**：为了存储不同类型的消息，本项目使用“函数萃取”技术提取可调用对象的调用形式（call signature），然后使用 boost 库中的 any 类来擦出对象的类型。
 - **消息的发布**：在发布消息时，发布者需要提供消息的主题（Topic）以及泛型函数对应的实参（如果需要的话）。消息总线会遍历消息列表，发布对应类型的消息。

## 运行环境

 - 本项目使用了 [boost 库][8] 的头文件，安装方法如下（以 Ubuntu 为例）：
    
```
sudo apt-get install libboost-dev
```

## 使用示例
```
//创建消息总线
MessageBus MsgBus;

//添加消息（传入可调用对象以及主题Student）
MsgBus.AddMsg([](int id){ cout << "Student ID: " << id << endl; } , "Student");

//发布消息（发布 Student 主题的消息）
MsgBus.SendMsg<void, int>(123, "Student");

//删除消息（删除 Student 主题的消息）
MsgBus.RemoveMsg<void, int>("Student");
```

## 技术细节

 - **函数萃取**

该项目使用的函数萃取（Function traits）是一种特殊的 Traits class。

> 《Effective C++》条款47：Traits classes 使得“类型相关信息”在编译期可用。它们以 templates 和 “templates特化”完成实现。

> 使用 Traits class 的方法：
① 建立一组重载函数（身份像劳工）或函数模版，彼此间的差异只在于各自的 traits 参数。令每个函数实现码与其接受之 traits 信息相应和。
② 建立一个控制函数（身份像工头）或函数模版，它调用上述那些“劳工函数”并传递 traits class 所提供的信息。

[Function traits][9] 通过模版特例化和可变参数模版在编译期间获取函数类型。

本项目中较难实现的是 lambda 表达式等可调用对象的类型萃取。当我们编写了一个 lambda 后，编译器将该表达式翻译成一个未命名类的未命名对象，该类中含有一个重载的函数调用运算符。当我们向 FunctionTraits< T >传入一个 lambda 表达式时，实际上是传入了一个类对象。然后利用模版特化 &T::operator() 得到指向成员函数的指针，最后使用特化模版 RetType(ClassType::*)(Args...)进行处理。其它可调用对象的处理方法与此相似。

 - **any 类**

[any 类][10]是 boost 库中的一个特殊容器，可以存放任何类型的值，在使用时可调用  [any_cast<T>][11]将对象还原为实际类型。 

 - **转发和可变参数模版**

《C++ Primer》中文版 p.624

![Args][12]
 
 ## 延伸阅读
 
 [Alan Kay On Messaging][13]


  [1]: https://stackoverflow.com/questions/3987391/why-people-use-message-event-buses-in-their-code
  [2]: https://ardalis.com/bus-or-queue
  [3]: https://github.com/whichxjy/MessageBus/blob/master/images/Message-Bus.png
  [4]: https://en.wikipedia.org/wiki/Publish%E2%80%93subscribe_pattern
  [5]: https://github.com/ServiceStack/ServiceStack.Redis/wiki/RedisPubSub
  [6]: https://hackernoon.com/observer-vs-pub-sub-pattern-50d3b27f838c
  [7]: https://github.com/whichxjy/MessageBus/blob/master/images/PubSub.gif
  [8]: https://www.boost.org/
  [9]: https://www.boost.org/doc/libs/1_41_0/libs/type_traits/doc/html/boost_typetraits/reference/function_traits.html
  [10]: https://www.boost.org/doc/libs/1_61_0/doc/html/boost/any.html
  [11]: https://www.boost.org/doc/libs/1_42_0/doc/html/boost/any_cast.html
  [12]: https://github.com/whichxjy/MessageBus/blob/master/images/args.jpg
  [13]: http://wiki.c2.com/?AlanKayOnMessaging
