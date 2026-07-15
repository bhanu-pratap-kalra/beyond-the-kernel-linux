# Beyond the Kernel | Modern C++ & Linux | Day 13 - Pass by Value vs `const&` vs `&&` - Choosing the Right Function Parameter

In Day 12, we looked at `std::string_view` and how it helps avoid unnecessary string copies.

Today, let's look at another important Modern C++ design decision:

**How should we pass objects to a function?**

Let's understand the three common approaches.

---

## Pass by Value

```cpp
void lets_study_function_parameter(BigObject big_object)
{
}
```

Passing by value creates a new object for the function parameter.

Depending on the argument, this may involve a copy or a move.

This is useful when the function needs its own independent object.

---

## Pass by `const` Reference

```cpp
void lets_study_function_parameter(const BigObject& big_object)
{
}
```

Here, no copy is made.

The function simply refers to the existing object and promises not to modify it.

This is often the preferred choice for large objects that only need to be read.

---

## Pass by Rvalue Reference

```cpp
void lets_study_function_parameter(BigObject&& big_object)
{
}
```

An rvalue reference accepts temporary objects or objects that the caller explicitly allows the function to move from.

This allows the function to transfer the object's resources instead of creating another copy.

> **Note:** An rvalue reference itself does not move the object. If the function wants to transfer the resources, it typically uses `std::move` on the named parameter.

```cpp
void lets_study_function_parameter(BigObject&& big_object)
{
    BigObject owned_object = std::move(big_object);
}
```

---

## Which One Should You Choose?

### Use pass by value when:

- The function needs its own copy
- Making a copy or move is part of the function's purpose
- Need your own copy? → Pass by value

### Use `const&` when:

- The function only needs to read the object
- You want to avoid unnecessary copies
- Only need to read the object? → Pass by `const&`

### Use `&&` when:

- The function intends to take ownership of the object's resources
- The caller is willing to give up the object's current value
- Need to take ownership of its resources? → Pass by `&&`

Choosing the right parameter type is not only about performance. It also communicates the function's intent to anyone reading your code.
