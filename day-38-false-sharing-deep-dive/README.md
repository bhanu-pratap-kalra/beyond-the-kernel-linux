# Beyond the Kernel | Modern C++ & Linux | Day 38 - False Sharing - Deep Dive

We first covered **false sharing back on Day 2**.

The idea was simple:

Two threads update different variables, but those variables accidentally live on the same cache line.

Now that we understand cache lines, locality and alignment, we can see exactly why that matters.

## Consider

```cpp
struct Counters
{
    std::atomic<int> first_thread_counter{0};
    std::atomic<int> second_thread_counter{0};
};
```

Each thread already has its own counter.

```text
Thread 1 -> first_thread_counter
Thread 2 -> second_thread_counter
```

No two threads are updating the same variable.

Sounds perfect.

But now look at the hardware view:

```text
One Cache Line

[first_thread_counter][second_thread_counter]
          ↑                     ↑
       Core 1                Core 2
```

The variables are independent.

**The cache line is not.**

When Core 1 writes `first_thread_counter`, it needs a writable copy of that cache line.

Then Core 2 wants to write `second_thread_counter`.

But `second_thread_counter` lives on the same cache line.

Conceptually:

```text
Core 1 writes
     ↓
Core 1 gets writable ownership
of the cache line
     ↓
Core 2 wants to write
     ↓
Core 2 needs that same cache line
     ↓
ownership changes
     ↓
Core 1 writes again
     ↓
line moves again
     ↓
repeat
```

So even though the threads are updating **different variables**, the cache-coherence mechanism still has to coordinate access to the **same cache line**.

That is **false sharing**.

## The Important Distinction

```text
C++ View
   ↓
different variables
   ↓
looks independent
```

```text
Hardware View
   ↓
same cache line
   ↓
not independent
```

This is also why atomics alone do not solve the performance problem.

```cpp
std::atomic<int>
```

can make an operation atomic and help with correctness.

But it does not guarantee that nearby atomic variables will behave independently at the cache-line level.

## Back on Day 2

We first had:

```cpp
struct FalseSharingVariables
{
    std::atomic<int> int_for_first_thread;
    std::atomic<int> int_for_second_thread;
};
```

The two variables may end up close together in memory and potentially share the same cache line.

Then we separated them:

```cpp
struct alignas(64) FalseSharingCorrectedVariables
{
    std::atomic<int> variable_for_single_thread;
};

FalseSharingCorrectedVariables for_thread1;
FalseSharingCorrectedVariables for_thread2;
```

Now the counters can be separated more like this:

```text
Cache Line 1
[counter for Thread 1................]

Cache Line 2
[counter for Thread 2................]
```

So the complete idea is:

```text
One counter per thread
        ↓
avoid multiple threads updating
the same variable
        ↓
separate those counters by cache line
        ↓
avoid false sharing
```

The deeper lesson is:

> **Logical separation in C++ does not automatically mean physical separation in memory.**

Two variables can be completely independent in our code and still interfere with each other because of the cache line containing them.

Next:

**Day 39 - `std::hardware_destructive_interference_size`**

Because `alignas(64)` is useful for understanding the idea, but C++17 gives us a better way to express the hardware interference boundary.

#Cpp #ModernCpp #Linux #Multithreading #FalseSharing #CPUCache #Atomics #PerformanceEngineering #LowLatency
