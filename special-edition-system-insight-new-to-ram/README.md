# Beyond the Kernel | Modern C++ & Linux

# Special Edition #2 – Systems Insight

## The Journey of `new` - From C++ to Physical RAM

Over the last few posts, we have explored how memory is managed in a modern C++ application. We started with the process memory layout, then looked at the stack and heap, function stack frames, dynamic memory allocation, virtual address space, and finally virtual memory.

Now let's connect everything together with a simple example.

```cpp
#include <memory>

class BigObject
{
    int data[10000];
};

int main()
{
    auto big_object = std::make_unique<BigObject>();
}
```

At first glance, this appears to be a simple object allocation.

Behind the scenes, however, several layers of software and hardware work together before `big_object` becomes usable.

---

## A Simplified Journey

```text
                  C++ Program
                       │
                       ▼
      std::make_unique<BigObject>()
                       │
                       ▼
                 operator new
                       │
                       ▼
      General Purpose Memory Allocator
   (glibc malloc / jemalloc / mimalloc ...)
                       │
                       ▼
               Operating System
                       │
                       ▼
        Process Virtual Address Space
                       │
                       ▼
            Address Translation
                       │
                       ▼
                 Physical RAM
                       │
                       ▼
          big_object Becomes Usable
```

---

## Let's briefly look at what each layer is responsible for.

### 1. C++ Allocation

The program requests memory using `new` or utilities such as `std::make_unique`.

At this stage, the program simply requests enough memory to construct a `BigObject`.

---

### 2. Memory Allocator

`operator new` typically delegates the allocation request to a general-purpose memory allocator, such as:

- glibc `malloc`
- jemalloc
- mimalloc
- tcmalloc

The allocator is responsible for managing dynamic memory and deciding how to satisfy the allocation request efficiently.

---

### 3. Operating System

If the allocator already owns suitable free memory, the allocation request may be satisfied immediately.

Otherwise, additional memory is requested from the operating system.

---

### 4. Process Virtual Address Space

The operating system provides memory within the process's virtual address space.

From the program's point of view, it is simply working with virtual addresses.

---

### 5. Address Translation

Whenever the program later accesses `big_object`, its virtual address is translated into a physical address before the CPU accesses memory.

---

### 6. Physical RAM

Once the translation is complete, the CPU reads from or writes to the corresponding location in physical memory.

From the program's perspective, this entire process is completely transparent.

---

# Key Takeaway

A single line of Modern C++ code such as:

```cpp
auto big_object = std::make_unique<BigObject>();
```

passes through multiple software and hardware layers before the object becomes usable.

Understanding this journey helps connect Modern C++, Linux, operating systems, and computer architecture into one complete mental model.

---

# What's Next?

In the next post, we'll begin exploring **paging** and see how operating systems divide virtual memory into manageable pages.

