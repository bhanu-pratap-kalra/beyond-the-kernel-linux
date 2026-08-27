# Beyond the Kernel | Modern C++ & Linux | Day 26 - Copy-on-Write - Share First, Copy Only When Needed

In Day 25, we explored **Demand Paging** - delaying physical memory work until a page is actually needed.

Copy-on-Write applies a similar idea:

**Why copy memory immediately if nobody has modified it yet?**

Two mappings can initially point to the **same physical page**.

```text
Process A Virtual Page ──┐
                         ├──► Physical Page
Process B Virtual Page ──┘
```

As long as both only read from it, sharing can continue.

But if one side tries to modify the page, the situation changes.

```text
Process A ─────► Original Physical Page

Process B
    │
    │ write
    ▼
Page Fault
    │
    ▼
Kernel creates a private copy
    │
    ▼
New Physical Page
```

Process B can now modify its own copy while Process A continues using the original.

That's **Copy-on-Write - COW**.

## A Simple Real-World Example

After a `fork()`, the parent and child can initially share the same physical pages.

If the child modifies one of those pages, the kernel creates a private copy for the child.

## Why Is This Useful?

Because copying memory can be expensive.

If the copy may never actually be needed, doing it upfront is wasted work.

Copy-on-Write allows the system to:

- Share memory initially
- Delay copying
- Copy only the pages that are actually modified

## A Few Fun Facts

- Copy-on-Write commonly relies on **page protection and page faults**.

- A shared page may initially be mapped in a way that lets the kernel detect the first write.

- The first write can trigger a page fault so the kernel can create a private copy.

- Copying normally happens at **page granularity**, not by copying an entire process address space at once.

- Copy-on-Write is an important reason `fork()` can be much cheaper than immediately duplicating all process memory.

So once again:

- A **page fault does not automatically mean failure**.
- Sometimes the fault is intentionally part of the operating system's memory-management strategy.

Next, we move to one of Linux's most important interfaces for creating and working with memory mappings:

**`mmap()`**

We'll explore that next.
