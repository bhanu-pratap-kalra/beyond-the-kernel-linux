# Beyond the Kernel | Modern C++ & Linux | Day 11 - `std::vector::resize()` vs `reserve() + emplace_back()` - Which One Should You Use?

In Day 9, we looked at `std::vector::reserve()`.

In Day 10, we saw how `emplace_back()` constructs objects directly inside the vector.

A natural question is:

> If I know I need exactly 100 objects, why not simply call `resize(100)`?

Let’s compare both approaches.

---

## Approach 1: `resize()`

```cpp
std::vector<BigObject> huge_vector_of_big_objects;

huge_vector_of_big_objects.resize(100);
```

If `BigObject` has a default constructor, `resize(100)` creates 100 objects directly inside the vector.

After this:

```text
size = 100
capacity >= 100
```

---

## Approach 2: `reserve()` + `emplace_back()`

```cpp
std::vector<BigObject> huge_vector_of_big_objects;

huge_vector_of_big_objects.reserve(100);

for (int i = 0; i < 100; ++i)
{
    huge_vector_of_big_objects.emplace_back();
}
```

Here, `reserve()` allocates enough storage upfront, and `emplace_back()` constructs each object directly inside that storage.

From a performance perspective, both approaches can avoid repeated reallocations and construct objects directly in vector storage.

However, there is still a difference in intent and overhead.

### `resize(100)`

- One clear operation
- One allocation in the usual case
- 100 direct object constructions

### `reserve(100)` + `emplace_back()`

- One allocation in the usual case
- 100 individual `emplace_back()` calls
- A loop and size update for every insertion

In an optimized build, the performance difference may be small.

But if all you need is 100 default-constructed objects, `resize(100)` is usually simpler and may have slightly less per-element insertion overhead.

However, if each object needs different constructor arguments, `reserve()` + `emplace_back()` is the better fit because every object is constructed directly with its own values.

```cpp
huge_vector_of_big_objects.reserve(100);

for (int i = 0; i < 100; ++i)
{
    huge_vector_of_big_objects.emplace_back(i, "object");
}
```

---

## Conclusion

- Need `N` default-constructed objects? Use `resize()`
- Need `N` individually constructed objects? Use `reserve()` + `emplace_back()`

Performance is not only about avoiding allocations. It is also about avoiding unnecessary operations and choosing the API that best matches the work being done.
