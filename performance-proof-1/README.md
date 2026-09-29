# Beyond the Kernel | Modern C++ & Linux | Performance Proof #1 - `std::vector` vs `std::list`

For the last few posts, we have talked about **cache lines, locality and data layout**.

Now let's measure one of the classic examples.

Both traversals are:

**O(n)**

```cpp
for (const auto& num : local_vector)
{
    vector_sum += num;
}

for (const auto& num : local_list)
{
    list_sum += num;
}
```

Algorithmically, they look almost identical.

Hardware-wise, they can behave very differently.

## `std::vector`

```text
[1][1][1][1][1][1]
```

Elements are contiguous.

A cache-line fetch can bring several upcoming values with it, giving us good **spatial locality** and a predictable access pattern.

## `std::list`

```text
[1] ----> [1] --------> [1] ---> [1]
```

Each node may live somewhere completely different in memory.

Traversal can become:

```text
load node
    ↓
follow pointer
    ↓
load another cache line
    ↓
follow pointer
    ↓
repeat
```

## Now the Interesting Part - The Measurement

I iterated through **100,000 elements** in each container and calculated the same sum.

```text
std::vector
Time: 63,417 ns

std::list
Time: 205,833 ns
```

Same number of elements.

Same sum.

Same **O(n)** complexity.

But in this test, the list traversal took **more than 3× as long**.

Why?

Not because Big-O was wrong.

Because Big-O does not describe the journey through the memory hierarchy.

## Algorithmic View

```text
vector traversal -> O(n)
list traversal   -> O(n)
```

## Hardware View

```text
vector -> contiguous + predictable

list   -> pointer chasing + scattered nodes
```

A `std::list` node also carries bookkeeping such as links to neighbouring nodes, while a `std::vector` packs the actual elements together.

So the CPU may get much more useful data from each cache-line fetch when traversing the vector.

Of course, this does **not** mean `std::list` is less useful than `std::vector`.

It has different properties, including:

- stable iterators
- efficient insertion when you already have the position
- efficient removal when you already have the position

But this little experiment demonstrates something important:

> **Same Big-O does not mean same performance.**

Sometimes the data structure that works better with the hardware wins by a very noticeable margin.

Next:

**Hardware Prefetching - How the CPU Tries to Guess What You'll Need Next**

#Cpp #ModernCpp #Linux #SystemsProgramming #STL #CPUCache #PerformanceEngineering #LowLatency
