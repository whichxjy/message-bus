# Message Bus

A simple message bus written in C++.

## Requirement

[boost](https://www.boost.org/)

## Example

``` cpp
// Create the message bus.
MessageBus messageBus;

// Every node has a topic it listen to and its own callback function.

// Create a node with a topic and a callback function.
messageBus.create("topic 1", [](int message) {
    // callback
    std::cout << "Node 1 get message: " << message << std::endl;
});

// Create another node.
messageBus.create("topic 1", [](int message) {
    // callback
    std::cout << "Node 2 get message: " << message << std::endl;
});

// Send message 123 to nodes that are listening to topic 1 and have the call signature void(int).
messageBus.push<void, int>("topic 1", 123);

// Remove nodes that are listening to topic 1 and have the call signature void(int).
messageBus.remove<void, int>("topic 1");

// No node will get this message now.
messageBus.push<void, int>("topic 1", 123);
```

## Publish/Subscribe Pattern

See [src/example.cpp](src/example.cpp).