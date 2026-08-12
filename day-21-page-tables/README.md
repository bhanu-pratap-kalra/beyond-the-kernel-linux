# Beyond the Kernel | Modern C++ & Linux | Day 21 - Page Tables - Where Virtual Memory Mappings Live

In the Day 20 post, we saw that virtual pages can map to different physical frames.

But where are these mappings actually stored?

The answer is **page tables**.

A page table is a data structure used by the virtual memory system to maintain mappings between virtual pages and physical memory.

## A simplified view

```text
Virtual Page    Page Table    Physical Frame

Page 0 ───►        8       ───► Frame 8
Page 1 ───►        3       ───► Frame 3
```

A page table entry contains more than just physical frame information.

It can also contain information such as:

- Whether the page is present
- Whether it can be read or written
- Whether user-space code can access it
- Other status and control information

This means page tables don't just help with **address translation**. They also play an important role in **memory protection and process isolation**.

But looking up page tables for every memory access could be expensive.

So how does the CPU make this faster?

That's where the **TLB - Translation Lookaside Buffer** comes in.

We will explore that next.
