# Beyond the Kernel | Modern C++ & Linux | Day 23 - Huge Pages - One Page Size Doesn't Fit All

On Day 22 post, we explored the **TLB**, which caches virtual-to-physical address translations.

Here's an interesting fact:

**Modern CPUs can support multiple page sizes.**

For example, on x86-64, you will commonly encounter:

```text
4 KB
  ↓
2 MB Huge Page
  ↓
1 GB Huge Page
```

## Why Larger Pages?

A larger page covers more memory with a single translation.

```text
Smaller Pages

[ ][ ][ ][ ][ ][ ][ ]...
          ↓
     More mappings


Larger Pages

[         ][         ]
          ↓
     Fewer mappings
```

Fewer mappings can mean **greater TLB reach** and lower page table overhead.

## A Few Fun Facts

- **4 KB is common, not universal** - page sizes depend on the architecture and OS/kernel configuration.

- Modern architectures such as **ARM64** can support different base page configurations.

- One **2 MB page** covers the same memory as **512 × 4 KB pages**.

- Linux supports **HugeTLB** for explicitly managed huge pages.

- Linux also supports **Transparent Huge Pages (THP)**, where the kernel can automatically use larger pages for eligible memory regions.

You can check your Linux system's base page size with:

```bash
getconf PAGE_SIZE
```

But bigger pages don't automatically mean better performance. They come with trade-offs around memory usage, fragmentation, allocation and workload characteristics.

**Page size is another engineering choice - not a "bigger is always faster" setting.**

So what happens when a process accesses a virtual page and the required mapping isn't available?

That's a **page fault**.

We will explore that next.
