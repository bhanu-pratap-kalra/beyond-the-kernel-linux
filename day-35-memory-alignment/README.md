# Beyond the Kernel | Modern C++ & Linux | Day 35 - Memory Alignment - Why, Where Your Object Starts Matters

On Day 34, we looked at hardware prefetching.

Today, let's look at something more fundamental:

**Memory alignment.**

Suppose we have:

```cpp
struct BigObject
{
    int id;
    double value;
};
```

A `double` typically prefers an address aligned to its natural boundary.

So the compiler may lay this out roughly like:

```text
[id][padding][value........]
```

That padding is not random waste.

It helps place `value` at an address suitable for its alignment requirement.

## Member Order Can Change Padding

Now compare:

```cpp
struct BigObject_1
{
    char c;
    double d;
    int i;
};
```

with:

```cpp
struct BigObject_2
{
    double d;
    int i;
    char c;
};
```

Same fields.

Different order.

Potentially different size because of padding.

That means alignment can affect:

- object size
- `struct` layout
- how many objects fit into a cache line
- memory footprint
- sometimes SIMD-friendly access

And C++ lets us ask directly:

```cpp
sizeof(BigObject);
alignof(BigObject);
```

## Explicit Alignment

C++ also lets us explicitly request alignment:

```cpp
alignas(64) struct BigObject
{
    double values[8];
};
```

We already saw `alignas()` back in **Day 2**, when discussing false sharing.

There, alignment helped keep independent data away from the same cache line.

Here, we're looking at the broader reason it works:

> **Objects have alignment requirements, and their starting addresses matter.**

## A Useful Mental Picture

Aligned:

```text
0x1000  [ BigObject ]

0x1040  [ BigObject ]

0x1080  [ BigObject ]
```

Poorly positioned / crossing a boundary:

```text
0x1038  [---- BigObject ----
0x1040        continues -----]
```

An object crossing a boundary is not automatically bad.

But depending on its size and access pattern, it may require touching more memory blocks than a better layout would.

And this matters even more when we start dealing with:

- cache lines
- SIMD / vector instructions
- custom allocators
- memory pools
- raw storage
- placement `new`

## Connection to the Low Latency C++ Lab

This should look familiar from the **Low Latency C++ Lab**, where raw storage had to respect:

```cpp
alignof(T)
```

because having enough bytes for an object is not enough.

Those bytes must also begin at a valid address for that type.

So:

```text
sizeof(T)
   ↓
How much memory?
```

and:

```text
alignof(T)
   ↓
Where may the object begin?
```

That distinction becomes very important once we stop letting ordinary `new` handle everything for us.

A useful rule:

> **Memory is not just about having enough bytes. Those bytes also need to be correctly positioned.**

Next:

**Cache Misses - What Actually Happens When the Data Isn't There**

#Cpp #ModernCpp #Linux #SystemsProgramming #MemoryAlignment #CPUCache #PerformanceEngineering #LowLatency
