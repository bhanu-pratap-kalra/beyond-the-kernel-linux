# Beyond the Kernel | Modern C++ & Linux | Day 10 - `push_back()` vs `emplace_back()`- Constructing Objects Directly Inside Containers

In Day 9, we looked at `std::vector::reserve()`.

The idea was simple: `reserve()` helps reduce repeated reallocations when we already know the expected number of elements.

But there is another small performance improvement we can make.

In Day 9, we used:

```cpp
for (int i = 0; i < 100000; ++i)
{
    huge_vector_of_big_objects.push_back(BigObject{});
}
```

Here, a temporary `BigObject` is created first.

Then `push_back()` inserts it into the vector, usually by moving it into vector storage.

So:

```text
push_back(BigObject{}) -> create object first, then move it into the vector
```

Now let’s compare it with `emplace_back()`:

```cpp
for (int i = 0; i < 100000; ++i)
{
    huge_vector_of_big_objects.emplace_back();
}
```

So:

```text
emplace_back() -> construct the object directly inside the vector
```

This is why `emplace_back()` can be useful when objects are expensive to create, copy, or move.

---

## A Better Pattern

A good way to write the code would be:

```cpp
std::vector<BigObject> huge_vector_of_big_objects;

huge_vector_of_big_objects.reserve(100000);

for (int i = 0; i < 100000; ++i)
{
    huge_vector_of_big_objects.emplace_back();
}
```

Here:

```text
reserve() reduces repeated reallocations
emplace_back() avoids unnecessary temporary construction
```

---

## Conclusion

- Do not blindly replace every `push_back()` with `emplace_back()`
- Use `emplace_back()` when you want to construct the object directly inside the container
- Use `push_back()` when you already have the object
- With `emplace_back()`, pass constructor arguments instead of creating a temporary object

Modern C++ performance is often about reducing unnecessary work. Sometimes that means reserving memory upfront. Sometimes that means constructing objects exactly where they need to live.
