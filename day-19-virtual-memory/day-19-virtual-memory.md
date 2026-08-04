# Beyond the Kernel | Modern C++ & Linux | Day 19 - Virtual Memory - Bridging Virtual Addresses and Physical Memory

In the previous post, we learned that every process is given its own **virtual address space**.

But the RAM installed in your computer contains **physical addresses**, not virtual ones.

So how does your program actually access memory?

The answer is **virtual memory**.

Every time a program accesses memory, it uses a **virtual address**. Before the CPU can read or write data, that virtual address is translated into a **physical address**.

---

## A Simplified View

```text
        Program
            │
            ▼
    Virtual Address
            │
            ▼
   Address Translation
            │
            ▼
    Physical Address
            │
            ▼
           RAM
```

---

## Some Interesting Facts

- Programs work with **virtual addresses**, not physical addresses.
- Each process has its own independent virtual address space.
- Virtual memory provides the illusion of one large, continuous address space.
- The operating system and hardware work together to translate virtual addresses into physical addresses.

---

## Why Is Virtual Memory Useful?

Virtual memory provides several important benefits:

- Process isolation
- Memory protection
- Efficient memory management
- The ability to use more virtual memory than the amount of installed RAM.
- Programs do not need to know where their data physically resides in RAM.

The exact mechanism behind this address translation depends on the operating system and processor architecture.

---

## Key Takeaway

A process never works directly with physical RAM addresses.

Instead, it works with **virtual addresses**, which are translated into **physical addresses** whenever memory is accessed.

---

## Looking Ahead

In the next post, we'll follow the complete journey of a memory allocation—from `new` in C++ all the way to physical RAM.
