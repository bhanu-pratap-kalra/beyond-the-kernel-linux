# Beyond the Kernel | Modern C++ & Linux | Day 20 - Paging - Breaking Virtual Memory into Pages

In the previous post, we saw that virtual addresses used by a process eventually need to be translated into physical memory. But how does the operating system manage this mapping efficiently?

The answer begins with **paging**. Instead of managing memory as one huge continuous region, virtual memory is divided into fixed size blocks called **pages**.

Physical memory is similarly divided into blocks called **page frames**.

## A simplified view

```text
Process Virtual Memory         Physical Memory

Virtual Page 0 ──────────────► Physical Frame 8
Virtual Page 1 ──────────────► Physical Frame 3
```

## Notice something important

The virtual pages appear continuous from the process's point of view, but their corresponding physical frames do not need to be next to each other in RAM.

For example, your program may see:

```text
Page 0  Page 1  Page 2  Page 3
```

as one continuous virtual region.

But physically they might reside in:

```text
Frame 8  Frame 3  Frame 15  Frame 6
```

This is one of the powerful abstractions provided by virtual memory.

## A few interesting facts

- Virtual memory is divided into pages
- Physical memory is divided into page frames
- A virtual page can be mapped to a physical frame
- Consecutive virtual pages do not require consecutive physical frames
- Page size depends on the architecture and OS configuration

So when our C++ program accesses an address, the system isn't simply asking:

> Where is this address in RAM?

Instead, part of the job is determining:

```text
Virtual Address
       │
       ▼
Virtual Page + Offset
       │
       ▼
Page Mapping
       │
       ▼
Physical Frame + Offset
       │
       ▼
Physical Address
```

This raises the next question:

**Where are these virtual page → physical frame mappings actually stored?**

That's where **page tables** enter the picture.

We will explore them next.
