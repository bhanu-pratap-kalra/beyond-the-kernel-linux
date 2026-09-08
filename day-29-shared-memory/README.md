# Beyond the Kernel | Modern C++ & Linux | Day 29 - Shared Memory - One Region, Multiple Processes

So far, we have seen how `mmap()` can create anonymous, private, file-backed, and shared mappings.

Now let's focus on one of the most interesting cases:

**Shared Memory**

Normally, each process has its own virtual address space.

```text
        Process A                    Process B
            │                            │
            ▼                            ▼
    Own Virtual Memory          Own Virtual Memory
```

But with shared memory, both processes can map virtual addresses that refer to the **same underlying physical memory**.

```text
Process A Virtual Page ──┐
                         ├──► Shared Physical Page
Process B Virtual Page ──┘
```

That means one process can write data and another process can read the same memory without copying it through an intermediate buffer.

## Why Is This Useful?

Shared memory can be useful for:

- Fast inter-process communication
- Large data exchange
- Shared queues or buffers
- Low-latency systems

But there's an important catch:

- Sharing memory does **not automatically make access safe**.
- If two processes modify the same data at the same time, we still need synchronization.

```text
        Shared Memory
             │
             ├── Process A writes
             │
             └── Process B writes
                      │
                      ▼
          Synchronization needed
```

So shared memory solves:

> **How can both processes access the same data?**

It does not automatically solve:

> **Who is allowed to modify it, and when?**

That takes us naturally toward **synchronization, atomics, locks, and lock-free structures**.
