# Beyond the Kernel | Modern C++ & Linux | Day 25 - Demand Paging - Memory When You Actually Need It

In Day 24 post, we saw something surprising.

**Not every page fault means something went wrong.**

Sometimes, it's exactly what the OS expects.

That's where **Demand Paging** comes in.

Instead of backing every virtual page with physical memory immediately, the OS can wait until that page is actually accessed.

## Think of It Like This

```text
Process gets a Virtual Memory Region
              │
              ▼
     Page not needed yet
              │
              ▼
      No physical page yet
              │
              ▼
         First Access
              │
              ▼
          Page Fault
              │
              ▼
       Kernel handles it
              │
              ▼
   Physical backing provided
              │
              ▼
      Process continues
```

## Why Do This?

Because a process may reserve or map much more virtual memory than it actually touches.

Demand paging lets the system avoid doing unnecessary work upfront.

## A Few Fun Facts

- Allocating or mapping virtual address space does **not necessarily mean physical RAM is immediately provided for every page**.

- The **first access** to a page can trigger a page fault as part of normal operation.

- The kernel can resolve the fault, establish the required mapping and restart the faulting instruction.

- This is one reason the **first touch of memory can behave differently from later accesses**.

- Demand paging helps physical memory be used for pages that are actually needed.

So page faults aren't always failures.

Sometimes they're simply the OS saying:

> **"You actually need this page now? Okay, let's provide it."**

But there's another clever virtual memory trick:

**What if two mappings initially share the same physical page and only get separate copies when someone tries to modify it?**

That's **Copy-on-Write**.

We'll explore that next.
