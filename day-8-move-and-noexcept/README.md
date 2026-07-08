# Beyond the Kernel | Modern C++ & Linux | Day 8 - `noexcept` and Move Semantics - Helping Containers Choose Move Over Copy

In Day 7, we looked at **move semantics**.

The key idea was simple: instead of copying the resource, move semantics can transfer ownership from one object to another.

```cpp
std::vector<int> target = std::move(source);
```

---

## What is `noexcept`?

`noexcept` tells the compiler that a function promises not to throw an exception.

So how is it related to move semantics?

Let’s understand it with an example from Day 7:

```cpp
class BigObject
{
public:
    BigObject() = default;

    BigObject(const BigObject&);       // Copy constructor declaration
    BigObject(BigObject&&) noexcept;   // Move constructor declaration, promises not to throw
};
```

Here, the move constructor is marked `noexcept`.

That means it promises not to throw an exception.

Why does this matter?

---

## Why `noexcept` Matters for Containers

Standard containers like `std::vector` sometimes need to move elements internally.

For example, when a vector grows and reallocates memory:

```cpp
std::vector<BigObject> big_objects;

big_objects.push_back(BigObject{});
big_objects.push_back(BigObject{});
big_objects.push_back(BigObject{}); // vector may need to reallocate
```

During reallocation, the vector may need to transfer existing elements to a new memory location.

If moving is marked `noexcept`, the vector can safely move the elements.

If moving is not `noexcept`, the vector may choose to copy instead, to maintain exception safety.

---

## Conclusion

- Move semantics gives a more efficient path
- `noexcept` tells the standard library that this efficient path is safe to use
- `noexcept` is not just documentation
- It can affect which code path the standard library chooses
- Simple rule: if your move constructor and move assignment cannot throw, mark them `noexcept`

Modern C++ performance is not only about moving resources, it is also about making those moves safe and visible to the standard library.
