# Beyond the Kernel | Modern C++ & Linux | Day 15 - Stack vs Heap - It's About Lifetime, Not Just Performance

## Introduction

A common misconception in C++ is:

> **"Use the stack because it's fast. Avoid the heap because it's slow."**

While this may sound like a useful rule of thumb, it doesn't explain the real difference between the two.

The fundamental distinction isn't speed—it's **how memory is managed and how long an object should live.**

---

## Example

```cpp
class BigObject
{
    int big_data[10000];
};

int main()
{
    BigObject big_object1;                 // Stack

    BigObject* big_object2 = new BigObject; // Heap

    delete big_object2;
}
```

Although both objects are created differently:

- Both have the same type.
- Both occupy the same amount of memory.
- The difference lies in **where they are allocated and how their lifetime is managed.**

---

## Stack

Objects created on the stack have **automatic storage duration**.

Characteristics:

- Created automatically when execution enters their scope.
- Destroyed automatically when execution leaves the scope.
- Lifetime is tied directly to the scope in which they are declared.
- No explicit memory management is required.

The compiler automatically manages the lifetime of stack objects.

---

## Heap

Objects created using dynamic allocation have **dynamic storage duration**.

Characteristics:

- Lifetime is controlled explicitly by the program.
- They continue to exist until they are destroyed.
- Modern C++ typically manages them using **RAII** and smart pointers rather than raw `new` and `delete`.
- Suitable when an object's lifetime must extend beyond the scope in which it was created.

> **Note:** Raw `new` and `delete` are used here only to demonstrate heap allocation. In production code, prefer smart pointers such as `std::unique_ptr` and `std::shared_ptr`.

---

## Allocation Overhead

Stack allocation typically has lower allocation overhead.

Heap allocation provides the flexibility to create objects whose lifetime is not tied to a particular scope.

Neither approach is inherently better, they solve different problems.

---

## Key Takeaway

Choosing between stack and heap is fundamentally a question of **object lifetime and ownership**.

Performance considerations come afterwards.

---

## Looking Ahead

In future posts, we'll explore how **memory layout**, **CPU caches**, and **cache locality** can have an even greater impact on performance than whether an object lives on the stack or the heap.
