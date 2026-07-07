# Beyond the Kernel | Modern C++ & Linux | Day 7 - RVO vs Move Semantics - Direct Construction vs Ownership Transfer

In Day 6 post, we looked at **RVO** and **NRVO**.

The key idea was simple: the object is constructed directly in its final destination.

```cpp
class BigObject {};

BigObject make_big_object()
{
    return BigObject{};  // RVO: constructed directly in the caller's storage
}
```

So in this case:

```text
RVO = no copy, no move
```

But what happens when an object already exists?

That is when **move semantics** becomes important.

---

## What is Move Semantics?

A move can transfer ownership of an internal resource from a source object to a target object.

The core idea is simple:

Instead of copying resources that are no longer needed by the source object, move the ownership.

Examples:

```cpp
std::string target_name = std::move(source_name);

std::vector<int> target_vector = std::move(source_vector);

std::unique_ptr<int> target_ptr = std::move(source_ptr);
```

Move semantics is useful when you already have a named object and want to transfer its resources.

In the above examples, `std::move` does not move anything by itself.

It casts the source objects into rvalue expressions so that a move constructor or move assignment operator can be used.

---

## RVO / NRVO vs Move Semantics

The contrast between **RVO / NRVO** and **move semantics** is:

- RVO / NRVO avoids creating extra objects where possible
- Move semantics efficiently transfers resources when an object already exists

---

## Caution with NRVO

Do not explicitly use `std::move` when returning a local object.

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
BigObject make_big_object_good_nrvo_candidate()
{
    BigObject big_object{};

    // Allows NRVO
    return big_object;
}
```

---

## Conclusion

- If the compiler can construct directly, let it
- If you no longer need the current owner object, but still need the resource it owns, move it instead of copying it

Modern C++ performance is not just about writing clever code, it is about understanding ownership, object lifetime, and when the compiler can help you.
