# Beyond the Kernel | Modern C++ & Linux | Day 40 - NUMA Basics - When RAM Is Not Equally Close to Every CPU

So far, we have talked a lot about getting data closer to the CPU.

Now let's go one step beyond.

On many multi-socket or large server systems, memory is not equally close to every CPU.

That is where **NUMA - Non-Uniform Memory Access** comes in.

```text
NUMA Node 0
CPU(s) + Local RAM 0

NUMA Node 1
CPU(s) + Local RAM 1
```

If a thread on Node 0 accesses memory on Node 0:

```text
CPU 0 -> Local RAM 0
```

Great.

If it accesses memory attached to another node:

```text
CPU 0 -> Remote RAM 1
```

that access usually has to travel farther.

That can mean:

> **more latency + more traffic**

So NUMA performance is really about:

> **Where does the memory live, and where is the thread running?**

## First Touch

One important factor is **first touch**.

```cpp
std::vector<BigObject> big_objects(large_size);

for (auto& big_object : big_objects)
{
    // Process BigObject
}
```

On many Linux NUMA systems, the thread that first touches a page can influence which NUMA node gets the physical memory.

But first touch is only one piece of the story.

## What Else Can Affect NUMA Locality?

- **Thread affinity** → which CPU / NUMA node the thread runs on
- **Scheduler migration** → the OS may move the thread somewhere else
- **Memory policy** → pages can be bound, preferred or interleaved across nodes
- **Page migration** → the OS may move pages as access patterns change
- **Shared data** → threads on different nodes may all access the same memory
- **Thread pools / work stealing** → work may run far from where its data was allocated
- **Huge pages** → placement and migration happen at a larger granularity
- **Virtualization** → the guest NUMA topology may differ from the physical host

## A Useful Mental Model

```text
Cache Locality
    ↓
keep data close to the CPU core


NUMA Locality
    ↓
keep data close to the CPU / socket using it
```

And the important part is:

> **NUMA is not just about where memory was initialized.**

It is about:

```text
Where memory lives
        +
Where the thread runs
        +
Whether either one moves
```

That is why a program can have:

- good algorithms
- good cache locality
- good threading

and still lose performance because memory is being accessed remotely.

Next:

**Day 41 - Memory Barriers**

#Cpp #ModernCpp #Linux #NUMA #MemoryPerformance #CPUCache #PerformanceEngineering #LowLatency
