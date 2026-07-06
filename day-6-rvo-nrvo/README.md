# Beyond the Kernel | Modern C++ & Linux | Day 6 - RVO and NRVO: When Return by Value Does Not Mean Copy

One of the elegant performance features in Modern C++ is that a function can return a heavy object by value and still avoid unnecessary copies.

This is where **RVO** and **NRVO** come in.

---

## What is RVO?

**RVO** stands for **Return Value Optimization**.

Let’s understand it with an example:

```cpp
class BigObject {};

BigObject make_big_object()
{
    // RVO: guaranteed direct construction in the final destination since C++17
    return BigObject{};
}
```

At first glance, it looks like this function creates a temporary `BigObject`, then copies or moves it back to the caller.

But Modern C++ does not have to work that way.

Since C++17, this is not just an optimization anymore. For prvalues like `BigObject{}`, the object is constructed directly in the final destination.

There is no temporary object to move from.

---

## What is NRVO?

**NRVO** stands for **Named Return Value Optimization**.

Let’s understand it with another example:

```cpp
BigObject make_big_object_nrvo()
{
    BigObject big_object{};

    // NRVO candidate: optimization not guaranteed
    return big_object;
}
```

Here, `big_object` is a named local variable.

The compiler is allowed to construct `big_object` directly into the caller’s return storage.

If it does, there is no copy and no move.

But unlike guaranteed prvalue return, NRVO is still optional. The compiler may apply it, but the standard does not force it.

---

## Where RVO and NRVO Help

RVO and NRVO are useful when:

- Returning large objects like containers
- Returning RAII wrappers or objects with clear ownership
- Creating clean factory functions
- Keeping APIs readable
- Getting compiler-friendly performance

---

## Caution with NRVO

Do not explicitly use `std::move` when returning a local object.

Let’s understand this with another example:

```cpp
BigObject make_big_object_bad_nrvo_candidate()
{
    BigObject big_object{};

    // This usually hurts NRVO
    return std::move(big_object);
}
```

NRVO works when the return expression is the name of a local object.

`std::move(big_object)` changes the expression category and can prevent NRVO.

If NRVO cannot happen, Modern C++ already has move fallback rules.

So prefer this:

```cpp
return big_object;
```

Instead of this:

```cpp
return std::move(big_object);
```

---

## Conclusion

- Do not fear returning objects by value
- Modern C++ wants you to write value-oriented code
- The compiler is often smart enough to make it efficient
