# Beyond the Kernel | Modern C++ & Linux | Day 32 - Spatial vs Temporal Locality

On Day 31, we saw that CPUs fetch **cache lines**, not just one variable.

That gives us two very useful ideas:

- **Spatial locality** → use nearby data soon
- **Temporal locality** → reuse the same data soon

## Spatial Locality

Consider:

```cpp
std::vector<int> my_values{10, 20, 30, 40, 50, 60};

for (int my_value : my_values)
{
    sum += my_value;
}
```

`std::vector` keeps its elements close together in contiguous memory:

```text
[10][20][30][40][50][60]
```

When the CPU fetches one cache line, several upcoming values may already be there.

That is **spatial locality**.

## Temporal Locality

Now consider:

```cpp
const int my_const_value = 10;

for (int i = 0; i < 1'000'000; ++i)
{
    sum += my_const_value;
}
```

The same value is used repeatedly.

If it remains in cache, the CPU can reuse it instead of fetching it again from farther away in the memory hierarchy.

That is **temporal locality**.

## The Easy Way to Remember

```text
Spatial  -> "I will probably need your neighbour."

Temporal -> "I will probably need you again."
```

And this is where C++ choices start to matter.

Things like:

- `std::vector` vs `std::list`
- object size
- hot vs cold data
- memory pools
- `struct` layout
- iteration patterns

can all affect locality.

A useful performance mindset is:

> **Use nearby data together, and reuse data while it is still hot.**

Next:

**Cache Locality - Why Data Layout Matters**

#Cpp #ModernCpp #Linux #SystemsProgramming #CPUCache #PerformanceEngineering #LowLatency
