# Beyond the Kernel | Modern C++ & Linux

# Special Edition #1 - 14 Modern C++ & Linux Edge Cases That Every C++ Developer Should Know

We have covered quite a few Modern C++ concepts over the last 14 posts. Before we move deeper into Linux internals, let's take a quick pause and revisit some of the most interesting edge cases we have seen so far.

These are small details, but they often appear in code reviews, performance debugging, and real world software development.

---

# 1. Returning `std::move(local_variable)` may disable NRVO

```cpp
BigObject make_big_object_bad_nrvo_candidate()
{
    BigObject big_object{};

    return std::move(big_object);
}
```

Instead of helping performance, `std::move()` may prevent **Named Return Value Optimization (NRVO)**.

---

# 2. `std::move()` doesn't actually move anything

```cpp
std::move(big_object);
```

`std::move()` simply casts an object to an rvalue.

The actual move only happens if a move constructor or move assignment operator is invoked.

---

# 3. `noexcept` can make `std::vector` faster

If your move constructor isn't marked `noexcept`, `std::vector` may choose to copy elements during reallocation instead of moving them.

---

# 4. `reserve()` does not create objects

```cpp
std::vector<BigObject> huge_vector_of_big_objects;

huge_vector_of_big_objects.reserve(100);
```

After this call:

```cpp
huge_vector_of_big_objects.size() == 0;
huge_vector_of_big_objects.capacity() >= 100;
```

Only memory is reserved.

No objects are constructed.

---

# 5. Calling `reserve()` with a smaller value does nothing

```cpp
std::vector<BigObject> huge_vector_of_big_objects;

huge_vector_of_big_objects.reserve(100);

huge_vector_of_big_objects.reserve(50);
```

The capacity remains **100**.

`reserve()` can only increase capacity.

It never shrinks it.

---

# 6. Growing an existing vector with `reserve()` may invalidate iterators

```cpp
huge_vector_of_big_objects.reserve(200);
```

If a reallocation occurs, all existing pointers, references, and iterators become invalid.

---

# 7. `resize()` creates objects immediately

```cpp
huge_vector_of_big_objects.resize(100);
```

Unlike `reserve()`, `resize()` actually constructs 100 objects.

---

# 8. `emplace_back()` is not always better

```cpp
huge_vector_of_big_objects.emplace_back(existing_big_object);
```

If the object already exists, `push_back()` is often equally good.

`emplace_back()` shines when constructing the object directly inside the container.

---

# 9. `std::string_view` can become dangling

```cpp
std::string_view my_string_view;

{
    std::string my_temp_text = "C++";

    my_string_view = my_temp_text;
}
```

`my_temp_text` has been destroyed.

`my_string_view` now refers to invalid memory.

---

# 10. An rvalue reference parameter becomes an lvalue inside the function

```cpp
void foo(BigObject&& big_object)
{
    // big_object is an lvalue here
}
```

If you want to transfer ownership again, you still need:

```cpp
std::move(big_object);
```

---

# 11. The pointer and the object can live in different memory regions

```cpp
int* my_local_pointer_lives_in_stack = new int(10);
```

- `my_local_pointer_lives_in_stack` lives on the **stack**
- `*my_local_pointer_lives_in_stack` lives on the **heap**

---

# 12. Global variables in `.bss` are not garbage

```cpp
int my_global_uninitialized_bss;
```

Although it is uninitialized in the source code, the operating system zero initializes it before `main()` starts.

---

# 13. String literals usually live in `.rodata`

```cpp
const char* my_global_message = "Beyond the Kernel";
```

Typically,

- `my_global_message` (the global pointer) lives in **`.data`**
- `"Beyond the Kernel"` (the string literal) lives in **`.rodata`**

---

# 14. `std::move()` does not guarantee a move

```cpp
std::move(big_object);
```

Even after writing `std::move()`, the compiler may still perform a copy if the type has no usable move constructor.

---

# Conclusion

- Modern C++ isn't difficult because of its syntax.
- It's difficult because of the small details.
- Understanding these edge cases will help you write faster, safer, and more predictable code.

These small details are easy to overlook, but they often separate code that simply works from code that is efficient, maintainable, and production ready.
