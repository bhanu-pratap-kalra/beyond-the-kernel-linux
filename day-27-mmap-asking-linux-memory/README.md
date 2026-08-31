# Beyond the Kernel | Modern C++ & Linux | Day 27 - mmap() - Asking Linux for Memory Directly

So far, we have explored **Virtual Memory, Page Faults, Demand Paging and Copy-on-Write**.

Now let's look at one practical Linux interface behind many memory-management systems:

**`mmap()`**

One use of `mmap()` is to create **anonymous memory**.

That simply means:

**Give my process a virtual-memory region that is not representing the contents of a normal file.**

```text
                Process
                   │
                   ▼
                 mmap()
                   │
                   ▼
        Virtual Memory Region
                   │
                   ▼
   Physical pages provided as needed
```

From the application's point of view, this becomes ordinary readable/writable memory.

So how is this different from `new` or `malloc`?

```text
              new / malloc
                   │
                   ▼
        General-Purpose Allocator
                   │
                   ▼
        May request larger regions
        from the operating system
                   │
                   ▼
                 mmap()
```

`new` and `malloc` are **higher-level allocation interfaces**.

`mmap()` is a **lower-level Linux virtual-memory interface**.

For sufficiently large allocations, a general-purpose allocator may obtain memory from the operating system using `mmap()` and then manage that region itself.

## Connecting This to the Low-Latency C++ Lab

Our memory pool currently:

```text
        Preallocates Storage
                 │
                 ▼
        Divides it into Slots
                 │
                 ▼
         Reuses those Slots
```

A future version could instead do:

```text
                mmap()
                  │
                  ▼
        Large Memory Region
                  │
                  ▼
             Memory Pool
                  │
          ┌───────┼───────┐
          ▼       ▼       ▼
        Slot    Slot    Slot
```

The pool could obtain a large region once and then manage allocations internally instead of requesting memory for every object.

That's the key idea:

**`mmap()` can provide the memory region.**

**The allocator or memory pool decides how that region is used.**

And because of **Demand Paging**, creating a large virtual mapping does not necessarily mean every page immediately consumes physical RAM.

There is much more to `mmap()`:

- File mappings
- Copy-on-Write mappings
- Shared memory

We'll build on those next.
