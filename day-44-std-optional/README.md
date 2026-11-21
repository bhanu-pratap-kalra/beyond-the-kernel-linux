# Beyond the Kernel | Modern C++ & Linux | Day 44 - `std::optional` - When a Value May or May Not Exist

Sometimes a function has a valid result.

Sometimes it simply doesn't.

Traditionally, we often handled that with magic values:

```cpp
int find_index(...)
{
    // ...
    return -1;
}
```

But now `-1` has a hidden meaning:

> **No value found.**

That works, but the meaning lives in our convention.

C++17 gives us a clearer option:

```cpp
std::optional<int> find_index(...)
{
    if (found)
    {
        return index;
    }

    return std::nullopt;
}
```

Now the return type itself tells us:

> **This function may return an `int`, or it may return nothing.**

## Usage

```cpp
auto result = find_index(...);

if (result)
{
    std::cout << *result;
}
```

Or:

```cpp
if (result.has_value())
{
    std::cout << result.value();
}
```

Both are valid ways to check whether the `std::optional` contains a value.

## Another Example

```cpp
std::optional<BigObject> get_big_object(int id)
{
    if (id < 0)
    {
        return std::nullopt;
    }

    return BigObject{};
}
```

Now we have:

- no special pointer
- no fake object
- no magic integer

The absence of a value is represented explicitly.

## Providing a Fallback

If we want a default value when the optional is empty:

```cpp
int value = result.value_or(-1);
```

This means:

```text
optional contains a value
        ↓
use that value

optional is empty
        ↓
use -1
```

That can make the intent much clearer.

## `std::optional` Is Not the Same as Error Handling

Sometimes "nothing found" is perfectly valid.

```text
optional
   ↓
value may legitimately be absent


error
   ↓
something actually went wrong
```

That distinction can make APIs much easier to understand.

The bigger lesson is:

> **Good C++ types should communicate intent.**

Instead of returning a value and hoping the caller knows what `-1`, `nullptr`, or some other sentinel means, `std::optional` makes:

> **"Maybe there is a value."**

part of the type itself.

Next:

**Day 45 - `std::variant` and `std::expected` - When a Value Can Have More Than One Meaning**

#Cpp #ModernCpp #Linux #Optional #Cpp17 #SystemsProgramming #SoftwareEngineering
