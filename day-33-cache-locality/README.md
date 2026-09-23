# Beyond the Kernel | Modern C++ & Linux | Day 33 - Cache Locality - Why Data Layout Matters

On Day 32, we looked at:

- **Spatial locality** → use nearby data soon
- **Temporal locality** → reuse the same data soon

Now let's make it practical with a familiar object from this series.

```cpp
struct BigObject
{
    int id;                // hot
    double value;          // hot

    char metadata[256];    // cold
};
```

Suppose our hot path only does this:

```cpp
for (auto& big_object : big_objects)
{
    big_object.value += 1.0;
}
```

The loop only cares about `value`.

But each `BigObject` carries a large `metadata` block beside it:

```text
[id][value][------------- metadata -------------]
      ↑
    useful
```

Because the CPU fetches **cache lines**, some of that cold data may occupy valuable cache space even though the loop never touches it.

## Separating Hot and Cold Data

Now imagine separating the data:

```cpp
struct BigObjectHot
{
    int id;
    double value;
};

struct BigObjectCold
{
    int id;                // duplicated to associate it with the hot object
    char metadata[256];
};
```

Duplicating the `id` uses a little more storage, but it gives us a simple way to associate the hot and cold parts of the same logical object.

The hot objects now look more like:

```text
[id][value][id][value][id][value][id][value]...
```

More useful data can fit into each cache line.

That is **cache locality by design**.

Another option is to keep the hot and cold objects in matching arrays and use their index as the relationship:

```cpp
std::vector<BigObjectHot> hot_objects;
std::vector<BigObjectCold> cold_objects;

// hot_objects[i] and cold_objects[i]
// belong to the same logical object
```

This can avoid duplicating the ID entirely.

## Container Choice Matters Too

The same idea appears when choosing containers.

```cpp
std::vector<BigObjectHot>
```

stores its elements contiguously:

```text
[big_object][big_object][big_object][big_object][big_object]
```

While pointer-heavy structures may scatter objects around memory:

```text
big_object -----> big_object ----------> big_object ---> big_object
```

Same objects.

Same loop.

Very different memory behaviour.

## Array of Structures vs Structure of Arrays

There's another interesting layout choice.

### Array of Structures

```text
[id value][id value][id value][id value]
```

### Structure of Arrays

```text
[id    id    id    id   ]
[value value value value]
```

If a hot loop only needs `value`, the second layout can pack many more useful values together.

This is where cache-aware C++ starts becoming very practical.

**Object size, field placement, container choice and access pattern can all change how much useful data we get from every cache-line fetch.**

A useful question to ask is:

> **When the CPU loads one cache line, how much of it am I actually going to use?**

Next:

**Performance Proof #1 - `std::vector` vs `std::list`**

Let's measure what all this looks like in practice.

#Cpp #ModernCpp #Linux #SystemsProgramming #CPUCache #CacheLocality #PerformanceEngineering #LowLatency
