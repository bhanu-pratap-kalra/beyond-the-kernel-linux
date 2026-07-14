# Beyond the Kernel | Modern C++ & Linux | Day 12 - `std::string_view` -  Avoiding Unnecessary String Copies

In the last few posts, we focused on reducing unnecessary allocations and object construction.

Today, let's look at another Modern C++ feature introduced in **C++17**, `std::string_view`, and understand how it helps avoid unnecessary string copies.

Let's walk through an example:

```cpp
void print_my_string(const std::string& my_string)
{
    std::cout << my_string << '\n';
}
```

This works well for `std::string` objects.

But what if we also want to pass:

- A string literal
- A substring
- A character array

Now, let's look at the example below:

```cpp
#include <string_view>

void print_my_string_view(std::string_view my_string_view)
{
    std::cout << my_string_view << '\n';
}
```

Now the same function can accept:

```cpp
std::string my_string = "C++17";

print_my_string_view(my_string);

print_my_string_view("Modern C++");

print_my_string_view(std::string_view{my_string}.substr(0, 3));
```

So what makes `std::string_view` useful?

Unlike `std::string`, a `std::string_view` does not own the characters.

It simply points to an existing character sequence along with its length.

---

## Simple Comparison

- `std::string` → Owns the characters
- `std::string_view` → Views the characters

As it does not own the data, creating a `std::string_view` is typically inexpensive and avoids creating another `std::string`.

---

## One Important Rule

A `std::string_view` is only valid while the underlying character data remains valid.

Let's understand this with another example:

```cpp
std::string_view my_bad_string_view;

{
    std::string my_string = "C++17";
    my_bad_string_view = my_string;
} // my_string is destroyed here

// my_bad_string_view is now dangling
```

---

## Conclusion

- `std::string_view` is a non-owning view of a string
- It can help avoid unnecessary string copies
- It works well for read-only function parameters
- Ensure the underlying string outlives the `std::string_view`

Modern C++ performance is not only about avoiding allocations. Sometimes it is simply about avoiding ownership when ownership is not required.
