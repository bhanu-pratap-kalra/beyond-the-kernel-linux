# Beyond the Kernel | Modern C++ & Linux | Day 24 - Page Faults - When the OS Has to Step In

We have explored **page tables, the TLB and Huge Pages**.

Now an important distinction:

**A TLB miss is NOT the same as a page fault.**

Consider a memory access:

```text
CPU accesses Virtual Address
            │
            ▼
        Check TLB
         /     \
       HIT     MISS
        │        │
        │        ▼
        │   Page Table Walk
        │        │
        │    ┌───┴──────────┐
        │    │              │
        │ Mapping        Access cannot
        │  found          be completed
        │    │              │
        │    ▼              ▼
        │ Continue       Page Fault
        │                   │
        ▼                   ▼
     Continue         Kernel steps in
```

## Think of It This Way

### TLB Miss

- I don't have this translation cached.
- The CPU can walk the page tables, find the mapping and continue.

### Page Fault

- I can't complete this memory access with the current page table state.
- Now the OS needs to step in.

And here's the interesting part:

- A page fault doesn't necessarily mean something went wrong.
- It can be part of normal virtual memory behaviour.
- The kernel may resolve the fault and let the process continue.

## A Few Fun Facts

- A **TLB miss** can be handled without a page fault.
- A **page fault is a CPU exception** that transfers control to the OS.
- Many page faults are completely normal and successfully resolved by Linux.
- Some faults are much more expensive than others.
- If the access cannot legally be resolved, Linux may deliver a signal such as **SIGSEGV**.

So why would Linux intentionally wait until memory is actually accessed before providing what the process needs?

That's **Demand Paging**.

We'll explore that next.
