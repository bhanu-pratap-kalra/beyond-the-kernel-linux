# Beyond the Kernel | Modern C++ & Linux | Day 30 - L1, L2 and L3 Cache - Why Data Layout Changes Performance

We have spent the last few posts following memory all the way to RAM.

But the CPU would really prefer **not** to go there.

That's why modern CPUs use a cache hierarchy:

```text
CPU Core
   │
   ▼
L1 Cache
   │
   ▼
L2 Cache
   │
   ▼
L3 Cache
   │
   ▼
RAM
```

The closer the data is to the CPU, the better.

Now imagine two C++ programs processing the same number of integers.

One uses a `std::vector`:

```text
[10][20][30][40]
```

The other walks a `std::list`:

```text
[10] -> [20] -> [30] -> [40]
```

Same number of elements.

Very different memory behaviour.

`std::vector` stores elements contiguously, so nearby values are more likely to arrive in cache together.

`std::list` follows pointers to nodes that may be scattered across memory.

That's where things get interesting.

## C++ Choices That Can Affect Cache Behaviour

- `std::vector` vs `std::list`
- Contiguous storage vs pointer chasing
- `struct` layout
- Member order, padding and object size

Let's take another example:

```cpp
struct BigObject_A
{
    char c;
    double d;
    int i;
}; // May occupy 24 bytes. Can you find why?
```

Now reorder the members:

```cpp
struct BigObject_B
{
    double d;
    int i;
    char c;
}; // May occupy 16 bytes. Can you find why?
```

The difference comes from **alignment and padding**.

Member order can reduce wasted padding and allow more objects to fit into cache lines.

## A Few More C++ Choices Quietly Influence Cache Behaviour

- **Smaller objects** → more useful objects can fit into the same cache line.

- **Hot vs cold data** → keep frequently accessed fields together so the CPU doesn't pull rarely used data into cache unnecessarily.

- **Memory pools** → reusing nearby preallocated storage can improve locality while also reducing allocation overhead.

- **`std::span`** → provides a lightweight, non-owning view over contiguous memory without copying it.

```cpp
void process(std::span<const int> values);
```

- **Cache-friendly iteration** → sequential access is usually much easier for caches and hardware prefetchers to predict than random access.

```cpp
for (const auto& value : values)
{
    sum += value;
}
```

- **`alignas(std::hardware_destructive_interference_size)`** → connects back to the false-sharing discussion from Day 2, where alignment can help separate frequently modified data across cache lines.

And there's another interesting connection:

## SIMD - Single Instruction, Multiple Data

When data is contiguous and the same operation is applied repeatedly, the CPU may be able to process several values together.

```text
[a1 a2 a3 a4]
       +
[b1 b2 b3 b4]
       ↓
[c1 c2 c3 c4]
```

So performance is not only about:

> **Which algorithm am I using?**

It is also about:

> **How is my data laid out, how will the CPU access it, and how much useful work can each cache load give me?**

That's where C++ data structures, object layout, locality, prefetching and SIMD all start connecting.

Next:

**Cache Lines** — because the CPU usually moves memory in chunks, not one variable at a time.

#Cpp #ModernCpp #Linux #SystemsProgramming #CPUCache #PerformanceEngineering #LowLatency
