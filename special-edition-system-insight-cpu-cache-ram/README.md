# Beyond the Kernel | Modern C++ & Linux | Special Edition #4 - System Insight - CPU to Cache to RAM

Over the last few posts, we covered:

- L1, L2 and L3 Cache
- Cache Lines
- Spatial and Temporal Locality
- Data Layout
- Hardware Prefetching
- Memory Alignment
- Cache Misses
- Branch Prediction

Now let's connect the whole journey.

When your C++ code accesses data:

```cpp
my_sum += my_values[i];
```

the CPU does not simply read from RAM.

A simplified path looks more like this:

```text
C++ Code
   │
   ▼
CPU Executes
   │
   ▼
L1 Cache
   │
   ├── Hit  → data ready
   │
   └── Miss
          │
          ▼
       L2 Cache
          │
          ├── Hit  → data ready
          │
          └── Miss
                 │
                 ▼
              L3 Cache
                 │
                 ├── Hit  → data ready
                 │
                 └── Miss
                        │
                        ▼
                       RAM
```

But even this is only part of the story.

The CPU also tries to stay ahead of you.

```text
Your Program
    │
    ├── Predictable Memory Access
    │            │
    │            ▼
    │    Hardware Prefetching
    │
    └── Predictable Control Flow
                 │
                 ▼
         Branch Prediction
```

So while your code is running, the CPU may already be asking:

> **What data will you need next?**

and:

> **Which instructions will you probably execute next?**

## Now Add Cache Lines

The CPU usually does not fetch just one variable.

You ask for:

```cpp
my_values[0];
```

The CPU may bring:

```text
[0][1][2][3][4][5]...
<------ cache line ------>
```

That is why layout matters.

```text
Good Layout
    ↓
Good Locality
    ↓
Useful Cache Lines
    ↓
Prefetcher Has an Easier Job
    ↓
Fewer Expensive Misses
    ↓
Less CPU Waiting
```

And this explains some of the C++ behaviour we measured.

```text
std::vector
    ↓
contiguous memory
    ↓
better locality
    ↓
predictable access
```

while:

```text
std::list
    ↓
pointer chasing
    ↓
scattered memory
    ↓
more difficult access pattern
```

Our earlier test showed:

```text
std::vector → ~63K ns
std::list   → ~205K ns
```

Same **O(n)**.

Very different hardware behaviour.

## Fast C++ Is More Than Just the Algorithm

When we talk about fast C++, the CPU is really dealing with several questions at once:

- Is the data already in cache?
- If not, where is it?
- Can I predict the next memory access?
- Can I predict the next branch?
- How much useful data came with this cache line?

And then comes the next interesting problem:

> **Two cores. Two threads. Two different variables. One shared cache line. Trouble can still start.**

Next:

**Day 38 - False Sharing - Advanced Deep Dive**

Where we'll look at what happens when the problem is not your variable, but the **cache line containing it**.

#Cpp #ModernCpp #Linux #SystemsProgramming #CPUCache #ComputerArchitecture #PerformanceEngineering #LowLatency
