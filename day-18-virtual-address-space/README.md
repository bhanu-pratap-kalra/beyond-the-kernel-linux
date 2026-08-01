# Beyond the Kernel | Modern C++ & Linux | Day 18 - Virtual Address Space - Every Process Gets Its Own View of Memory

In the previous post, we saw that memory can be allocated dynamically while a program is running.

But where does that memory actually come from?

The answer begins with the **virtual address space**.

Every process running on a modern operating system is given its own virtual address space.

---

## A Simplified View

```text
+-----------------------------------+
|               Stack               |
|     initially a small region      |
|                 ↓                 |
|                                   |
|    Unmapped Virtual Address       |
|              Space                |
|                                   |
|                 ↑                 |
|               Heap                |
|      starts small and can grow    |
+-----------------------------------+
| .bss                              |
| .data                             |
| .rodata                           |
| .text                             |
+-----------------------------------+
```

> **Note:** This is a simplified conceptual layout. The exact arrangement can vary between operating systems, processor architectures, executables, and individual process runs.

---

## A Few Interesting Facts

- `.text`, `.data`, `.rodata`, and `.bss` are mapped when the program starts.
- The heap begins as a relatively small mapped region and can grow as the program requests more memory.
- The stack starts with an initial mapped region and can grow as more stack space is required, subject to operating system limits.
- The large unmapped region is **not physical RAM**. It represents virtual addresses that can be mapped by the operating system when needed.

From your program's point of view, this appears to be one large, continuous block of memory.

In reality, virtual addresses are translated to physical memory by the operating system and hardware as the program executes.

---

## Why Is Virtual Address Space Useful?

Virtual address space provides several important benefits:

- Every process gets its own independent address space.
- Processes are isolated from one another.
- Memory regions can grow as an application's requirements change.
- Programs do not need to know where their data physically resides in RAM.

The exact size of a process's virtual address space depends on the operating system and processor architecture.

On modern 64-bit systems, the available virtual address space is typically much larger than the amount of physical RAM installed.

---

## Key Takeaway

A process does not work directly with physical RAM addresses.

Instead, it works with its own virtual addresses, which are translated to physical memory when required.

In the next post, we'll explore **virtual memory** and see how virtual addresses are mapped to physical memory.
