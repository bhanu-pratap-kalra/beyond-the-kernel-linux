# Beyond the Kernel | Modern C++ & Linux | Day 22 - TLB - A Cache for Address Translation

On Day 21, we saw that page tables maintain mappings between virtual pages and physical memory.

But there's a problem - our programs access memory constantly. Walking through page tables for every memory access would add significant overhead.

That's where the **TLB - Translation Lookaside Buffer** comes in.

The TLB is a small, fast cache inside the CPU that stores recently used virtual-to-physical address translations.

## A simplified journey

```text
CPU accesses a Virtual Address
              │
              ▼
         Check TLB
          /       \
       HIT         MISS
        │            │
        ▼            ▼
 Translation      Page Table
 available        lookup needed
        │            │
        └─────┬──────┘
              ▼
       Physical Memory
```

## TLB Hit

If the required translation is already in the TLB, the CPU can use the cached mapping without performing a page table walk.

## TLB Miss

If the translation isn't present, the processor needs to obtain the mapping through the page table mechanism and can then cache that translation in the TLB.

This gives us another important performance principle:

**Memory performance isn't only about whether your data is in the CPU cache. Address translation has caching behaviour too.**

And this raises another question:

**If the TLB is small, what happens when an application works with a very large number of pages?**

That's where **page size and Huge Pages** become interesting.

We will explore that next.
