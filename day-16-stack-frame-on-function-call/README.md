# Beyond the Kernel | Modern C++ & Linux | Day 16 - Function Stack Frames - What Happens When a Function Is Called?

## Introduction

In the Day 15 post, we saw that objects created on the stack have a lifetime tied to their scope.

But what actually happens when a function is called?

Let's understand this with an example.

---

## Example

```cpp
double calculate_order_value(double price, int quantity)
{
    double order_value = price * quantity;
    return order_value;
}

int main()
{
    double value = calculate_order_value(50.50, 100);
}
```

> **Interesting fact:** Although this function returns a value, it does **not** involve **NRVO (Named Return Value Optimization)**. NRVO is an optimization that applies when returning **named class-type objects**, whereas a fundamental type like `double` is typically returned directly according to the platform's calling convention.

---

## What Is a Stack Frame?

When `calculate_order_value()` is called, the program creates a **stack frame** for that function.

A stack frame typically contains:

- Function parameters (`price`, `quantity`)
- Local variables (`order_value`)
- The return address
- Other information required while the function executes

> **Note:** The exact contents of a stack frame are implementation-dependent. Compilers may keep some values in registers instead of storing them on the stack, especially with compiler optimizations enabled.

---

## A Simplified View

```text
+--------------------------------------+
| main()                               |
+--------------------------------------+
| calculate_order_value()              |
|  price                               |
|  quantity                            |
|  order_value                         |
+--------------------------------------+
```

This is a simplified conceptual view to illustrate how each function call has its own stack frame.

---

## What Happens When the Function Returns?

When `calculate_order_value()` finishes executing:

- Its stack frame is no longer needed.
- Local variables such as `order_value` are destroyed automatically.
- Execution resumes at the saved return address in the calling function.

---

## Things to Remember

- Every function call typically creates a new stack frame.
- A stack frame stores the information needed while a function executes.
- Local variables with automatic storage duration exist only for the lifetime of that stack frame.
- The exact layout depends on the compiler, optimization level, target architecture, and calling convention.

---

## Key Takeaway

Understanding stack frames makes it much easier to reason about:

- Function calls
- Local variable lifetime
- Recursion
- Debugging
- Stack overflows

Stack frames are one of the fundamental building blocks of how programs execute, making them an essential concept for every Modern C++ developer.
