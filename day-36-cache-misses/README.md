# Beyond the Kernel | Modern C++ & Linux | Day 36 - Cache Misses - What Happens When the Data Isn’t There

We have now looked at cache lines, locality, prefetching and alignment.

So what happens when the CPU finally asks:

> **Dude, where is my data?**

...and it is not in the cache?

That is a **cache miss**.

## Conceptually

```text
CPU needs data
     ↓
Check L1
     ↓
Miss
     ↓
Check L2
     ↓
Miss
     ↓
Check L3
     ↓
Miss
     ↓
Go towards RAM
```

The farther the CPU has to go, the more waiting is involved.

## Cache Miss != Page Fault

An important callback to our earlier memory posts:

A **cache miss is NOT a page fault**.

```text
Cache Miss
    ↓
Data may simply be in another cache level
or in RAM
```

while:

```text
Page Fault
    ↓
Virtual-memory mapping cannot currently
complete the access
    ↓
Kernel gets involved
```

Very different events.

## A Simple C++ Example

This is usually cache-friendly:

```cpp
for (const auto& value : my_vector)
{
    sum += value;
}
```

Why?

Because nearby values are stored together.

One cache-line load may satisfy several upcoming accesses.

Now imagine jumping around:

```cpp
sum += values[0];
sum += values[4096];
sum += values[8192];
sum += values[12288];
```

Now each access may land far away from the previous one.

Conceptually:

```text
use a little
    ↓
jump
    ↓
new cache line
    ↓
use a little
    ↓
jump again
```

More chances for cache misses.

## Not All Cache Misses Happen for the Same Reason

A few useful categories:

- **Cold miss** → first time the CPU touches the data
- **Capacity miss** → the working set is too large for the cache
- **Conflict miss** → different memory locations compete for the same cache placement

So sometimes your code can be perfectly sequential, but the working set simply does not fit.

That is why:

```text
Small working set
       ↓
fits in cache
       ↓
many cache hits
```

can behave very differently from:

```text
Huge working set
       ↓
cache constantly replaced
       ↓
more misses
```

## Connecting Everything So Far

```text
Good Data Layout
       ↓
Good Locality
       ↓
Useful Cache Lines
       ↓
Prefetcher Can Help
       ↓
Fewer Costly Misses
```

A useful performance question is:

> **Am I doing too much work, or is the CPU simply waiting for data?**

Those are not the same problem.

Next:

**Branch Prediction - When the CPU Tries to Guess Which Code Path Comes Next**

#Cpp #ModernCpp #Linux #SystemsProgramming #CPUCache #CacheMiss #PerformanceEngineering #LowLatency
