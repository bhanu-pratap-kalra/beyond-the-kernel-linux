# Beyond the Kernel | Modern C++ & Linux | Day 41 - Memory Barriers - When Order Starts to Matter

So far, we have talked about:

- Cache Lines
- False Sharing
- NUMA
- Multiple CPU cores working on shared memory

Now comes another question:

> **If one thread writes two things, will another thread always observe them in the same order?**

Not necessarily.

Let's understand with an example:

```cpp
my_value = 10;
my_value_is_ready = true;
```

At the C++ source level:

```text
1. write data
2. set ready
```

Looks obvious.

But modern CPUs and compilers can reorder operations when they are allowed to do so.

Why?

> **Performance.**

Now imagine another thread:

```cpp
if (my_value_is_ready)
{
    process(my_value);
}
```

What we want is:

```text
Thread 1

my_value = 10
    ↓
my_value_is_ready = true
```

and:

```text
Thread 2

sees my_value_is_ready == true
    ↓
must also see my_value == 10
```

This is where **atomics, memory ordering and memory barriers** come in.

## In C++

```cpp
std::atomic<bool> my_value_is_ready{false};

my_value = 10;

my_value_is_ready.store(
    true,
    std::memory_order_release
);
```

And:

```cpp
if (my_value_is_ready.load(std::memory_order_acquire))
{
    process(my_value);
}
```

The simple idea is:

```text
Release
   ↓
publish earlier writes


Acquire
   ↓
observe those writes
```

## Other Memory Ordering Options

C++ atomics also provide:

- `std::memory_order_relaxed` → atomicity with minimal ordering
- `std::memory_order_acquire` → ordering when reading
- `std::memory_order_release` → ordering when publishing
- `std::memory_order_acq_rel` → acquire + release
- `std::memory_order_seq_cst` → strongest standard ordering and the default for atomics

So if you simply write:

```cpp
std::atomic<int> counter{0};

counter++;
```

without explicitly specifying a memory order, C++ uses:

```cpp
std::memory_order_seq_cst
```

by default.

## Atomicity vs Memory Ordering

This is an important distinction:

```text
Atomicity
   ↓
Is this operation performed atomically?


Memory Ordering
   ↓
In what order can other memory operations
be observed around it?
```

The goal is not simply to use the weakest ordering because it sounds faster.

It is to use the ordering that correctly expresses what the threads need to observe.

A useful question in concurrent C++ is therefore not just:

> **Is this variable atomic?**

but:

> **What ordering guarantees does this operation actually need?**

Next:

**Performance Proof - Cache Friendly and Cache Unfriendly Layout**

#Cpp #ModernCpp #Linux #Concurrency #MemoryBarriers #Atomics #MemoryOrdering #PerformanceEngineering #LowLatency
