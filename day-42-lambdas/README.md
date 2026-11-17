# Beyond the Kernel | Modern C++ & Linux | Day 42 - C++ Lambdas - Functions Right Where You Need Them

After spending the last few weeks deep inside caches, NUMA and memory ordering, let's come back to modern C++.

Today:

**Lambdas**

Suppose we need a tiny function:

```cpp
int ProcessBigObject(BigObject big_object)
{
    // Process big_object
}
```

Perfectly fine.

But what if this behaviour is needed only once, right inside another piece of code?

C++ lets us write:

```cpp
auto ProcessBigObject = [](BigObject big_object)
{
    // Process big_object
};
```

and call it like:

```cpp
ProcessBigObject(BigObject{});
```

A lambda is basically:

> **A small function we can define exactly where we need it.**

## Basic Lambda Shape

```cpp
[](parameters)
{
    // code
}
```

The `[]` part is called the **capture list**.

And that is where lambdas become especially useful.

Suppose we already have:

```cpp
int num_iterations = 10;
```

We can capture it:

```cpp
auto ProcessBigObject = [num_iterations](BigObject big_object)
{
    // Process big_object num_iterations times
};
```

Now the lambda remembers the value of `num_iterations`.

## Capture by Value

```cpp
[num_iterations]
```

means the lambda gets its own copy of `num_iterations`.

## Capture by Reference

```cpp
[&num_iterations]
```

means the lambda works with the original variable.

For example:

```cpp
int my_counter = 0;

auto increment = [&my_counter]()
{
    ++my_counter;
};
```

Calling:

```cpp
increment();
```

changes the original `my_counter`.

## Lambdas With STL Algorithms

Lambdas become especially useful with STL algorithms.

Instead of creating a separate comparison function:

```cpp
std::sort(
    my_values.begin(),
    my_values.end(),
    [](int a, int b)
    {
        return a > b;
    }
);
```

Or filtering based on some condition:

```cpp
std::count_if(
    my_values.begin(),
    my_values.end(),
    [](int my_value)
    {
        return my_value > 100;
    }
);
```

## Lambdas With Threads

They are also common with threads:

```cpp
std::jthread worker([]()
{
    process();
});
```

## Why Do Lambdas Exist?

Lambdas let us:

- define small pieces of behaviour locally
- capture surrounding state
- avoid unnecessary helper functions
- pass behaviour directly to algorithms
- pass work directly to threads
- create callbacks easily

Common places you will see lambdas:

- STL algorithms
- sorting and filtering
- callbacks
- threads
- asynchronous code
- event handlers

A useful mental model is:

```text
Lambda
   =
local behaviour
   +
optional captured state
```

And there is something interesting happening underneath all this.

A lambda is not just some function syntax.

**The compiler actually creates an object behind it.**

That takes us to:

**Day 43 - Closure Objects - What a Lambda Really Becomes**

#Cpp #ModernCpp #Linux #Lambdas #STL #Concurrency #SystemsProgramming
