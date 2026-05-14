# Beyond the Kernel | Modern C++ & Linux | Day 2 - False Sharing

Recently revisited an interesting multithreaded performance issue 'False Sharing'.

False Sharing happens when two threads modify different variables, accidentally residing on the same CPU cache line. Even though they are logically unrelated, the CPU cache coherency mechanism keeps invalidating the cache line.


## Simple Example

struct FalseSharingVariables
{
    std::atomic<int> int_for_first_thread;
    std::atomic<int> int_for_second_thread;
};

As the two variables 'int_for_first_thread' and 'int_for_second_thread' belong to same struct, the compiler usually place them next to each other. An honest mistake, as on code level they are two independent variables.

As a result:
- both variables may end up sharing the same cache line
- different CPU cores continuously invalidate each others cache
- scalability and throughput may degrade


## C++11 Solution

C++11 introduced `alignas`, allowing explicit memory alignment in cache.

struct alignas(64) FalseSharingCorrectedVariables
{
    std::atomic<int> variable_for_single_thread;
};

FalseSharingCorrectedVariables for_thread1;
FalseSharingCorrectedVariables for_thread2;

This helps frequently modified variables to be on separate cache lines, reducing false sharing.


## C++17 Improvement

C++17 later introduced 'std::hardware_destructive_interference_size', allowing developers to avoid hardcoded cache line sizes and write more portable code.

Example:

struct alignas(std::hardware_destructive_interference_size) FalseSharingCorrectedVariables
{
    std::atomic<int> variable_for_single_thread;
};

FalseSharingCorrectedVariables for_thread1;
FalseSharingCorrectedVariables for_thread2;


## Key Takeaway

One thing I have learned over time is that performance bottlenecks are not always caused purely by software algorithms.

In highly concurrent systems, factors such as:
- memory layout
- cache locality
- synchronization
- CPU cache coherency
- hardware interaction

can have a surprisingly large impact on real world performance.

