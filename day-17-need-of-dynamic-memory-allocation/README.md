# Beyond the Kernel | Modern C++ & Linux | Day 17 - Why Do We Need Dynamic Memory Allocation?

## Introduction

In the previous posts, we've written examples like this:

```cpp
class BigObject
{
    int big_data[10000];
};

int main()
{
    BigObject big_object;
}
```

This works because the compiler already knows the size of `BigObject`.

It can reserve enough memory before the program even starts executing.

But what if the amount of memory required is only known while the program is running?

---

## Runtime Memory Allocation

```cpp
class BigObject
{
    int big_data[10000];
};

int main()
{
    int number_of_big_objects;
    std::cin >> number_of_big_objects;

    auto big_objects = std::make_unique<BigObject[]>(number_of_big_objects);
}
```

Here, the compiler does **not** know the value of `number_of_big_objects` in advance.

The required memory can only be determined while the program is running, so it must be allocated dynamically.

---

## When Is Dynamic Memory Allocation Useful?

Dynamic memory allocation becomes useful when:

- The amount of memory is only known at runtime.
- Objects need to be created or destroyed as the workload changes.
- The number of objects cannot be determined during compilation.

---

## A Real-World Example

Think about a low-latency trading system.

- New market data keeps arriving throughout the trading day.
- The application doesn't know beforehand how much memory it will need.
- Dynamic memory allocation allows it to request additional memory as more data arrives.

The same idea applies to many other applications, such as reading files, loading images, or receiving network packets. The amount of data often isn't known until the program is already running.

---

## Key Takeaway

Dynamic memory allocation isn't just about allocating memory on the heap.

It gives a program the flexibility to allocate memory **when** it is needed, rather than requiring everything to be known at compile time.

---

## Looking Ahead

In the next post, we'll zoom out and explore **where this dynamically allocated memory actually comes from** by looking at a process's **virtual address space**.
