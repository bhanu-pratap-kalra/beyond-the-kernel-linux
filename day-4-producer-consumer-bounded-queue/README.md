# Beyond the Kernel | Modern C++ & Linux | Day 4 - Producer Consumer with a Bounded Queue

One of the most important concurrency patterns in software engineering is the Producer Consumer pattern.

## The idea is simple

- A producer creates task
- A consumer process task
- A queue sits between them

But in real systems, we cannot assume that a queue will stay balanced forever. One may argue that modern consumers are fast enough to keep up with producers, but that is not always true. That is why one common way to handle this is to use a bounded queue with a reasonable fixed capacity suited to the system.

- If the queue is full, producers wait
- If the queue is empty, consumers wait

## Backpressure

This introduces backpressure into the system. Backpressure is important because:

- Memory can grown uncontrollably
- Latency can increase

## With a bounded queue

- Producers slow down when needed
- Consumers get time to catchup
- Memory remains controlled
- System behaves more predictably

## Modern C++ building blocks

In modern C++, this pattern is commonly implemented using

`std::mutex`
`std::condition_variable`
`std::queue`
`std::lock_guard`
`std::unique_lock`


## Key detail

A key detail is that `std::condition_variable::wait()` should be used with a predicate. This protects the thread from spurious wakeups, where a thread wakes up, even when the condition it was waiting for is still false.

## Final Thoughts

In concurrent systems, a queue is just not a container, it becomes a coordination point between safety, speed, memory and stability.
