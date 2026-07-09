# Beyond the Kernel | Modern C++ & Linux | Day 9 - `std::vector::reserve()` - Avoiding Unnecessary Reallocations

In Day 8 post, we looked at how `std::vector` may move or copy elements when it grows.Today, lets look at how we can reduce those reallocations in the first place.

Lets understand with an example:

```cpp
std::vector<BigObject> huge_vector_of_big_objects;

for (int i = 0; i < 100000; ++i)
{
    huge_vector_of_big_objects.push_back(BigObject{});
}
```

This code is simple and correct.

But as the vector grows, it may need to allocate new memory multiple times.

During each reallocation, existing `BigObject` elements may need to be moved or copied into the new memory block.

Now imagine the overhead when the vector becomes huge and repeated reallocations have to move or copy many `BigObject` elements.

Each reallocation can involve:

- Allocating new memory
- Moving or copying existing `BigObject` elements
- Releasing old memory

---

## Simple Solution: Use `reserve()`

If we already know roughly how many elements we need, we can use `reserve()`.

Now let’s revisit the above example again:

```cpp
std::vector<BigObject> huge_vector_of_big_objects;

huge_vector_of_big_objects.reserve(100000);

for (int i = 0; i < 100000; ++i)
{
    huge_vector_of_big_objects.push_back(BigObject{});
}
```

If the vector size never crosses `100000`, `reserve(100000)` can prevent further reallocations.

---

## Important Point

`reserve()` does not add elements.

It only prepares capacity.

So after the `reserve()` statement, the size is still `0`.

```cpp
std::vector<BigObject> huge_vector_of_big_objects;

huge_vector_of_big_objects.reserve(100000);

// size is still 0
// capacity is at least 100000
```

---

## Conclusion

- `reserve()` does not add elements; it only prepares capacity
- After calling `reserve()`, the vector size is still `0`
- If you know the expected number of elements, consider `reserve()`
- Do not use it everywhere
- Use it when you have a reasonable estimate of the final size

Modern C++ performance is often not about complex tricks. Sometimes, one line can avoid many hidden reallocations.
