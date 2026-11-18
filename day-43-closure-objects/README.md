# Beyond the Kernel | Modern C++ & Linux
## Day 43 — C++ Lambdas: Closure Objects, Captures & `mutable`

We use lambdas everywhere in modern C++, but what actually happens when the compiler encounters one?

**A lambda isn't just an anonymous function. It creates an object of a unique, unnamed closure type.**

Let's explore how closure types, objects, captures, and `mutable` work.

---

## 1. One Lambda, One Closure Type

```cpp
int my_factor = 10;

auto multiply = [my_factor](int x) {
    return x * my_factor;
};

multiply(2); // 20
multiply(3); // 30
```

Conceptually, the compiler generates something resembling:

```cpp
class Closure {
    int my_factor;

public:
    Closure(int f) : my_factor(f) {}

    int operator()(int x) const {
        return x * my_factor;
    }
};
```

The lambda expression creates a closure object, and `operator()` makes that object callable.

**One lambda expression → One closure type → One object → Multiple calls.**

Calling the same lambda repeatedly invokes `operator()` on the existing object. It does not create a new closure object for each call.

> **Note:** The generated class is conceptual. The C++ standard specifies closure-type behavior but doesn't require compilers to generate this exact class.

---

## 2. One Closure Type, Multiple Objects

```cpp
auto MakeMyMultiplier(int my_factor) {
    return [my_factor](int x) {
        return x * my_factor;
    };
}

auto a = MakeMyMultiplier(10);
auto b = MakeMyMultiplier(20);

a(5); // 50
b(5); // 100
```

Here:

- The lambda expression appears once.
- The compiler defines one unique closure type.
- Each function call creates a closure object.
- Both objects have the same type but independent captured values.

**One closure type → Multiple objects → Independent state.**

However, two separate lambda expressions have distinct closure types, even when their code is identical.

```cpp
#include <type_traits>

auto first  = [](int x) { return x * 2; };
auto second = [](int x) { return x * 2; };

static_assert(
    !std::is_same_v<
        decltype(first),
        decltype(second)
    >
);
```

---

## 3. Value vs Reference Capture

```cpp
int x = 10;

auto byValue = [x] { return x; };
auto byRef   = [&x] { return x; };

x = 20;

byValue(); // 10
byRef();   // 20
```

**Value capture `[x]`:**
- Stores a copy of `x` inside the closure object.
- Subsequent changes to the original `x` do not affect the captured copy.

**Reference capture `[&x]`:**
- Accesses the original variable.
- Changes to the original variable are visible to the lambda.
- The referenced variable must remain alive when the lambda accesses it.

Reference captures are particularly important in asynchronous code, where the lambda may outlive its original scope.

---

## 4. What Does `mutable` Do?

By default, a lambda's `operator()` is `const`, preventing modification of ordinary captured-by-value variables.

For example:

```cpp
int count = 0;

auto counter = [count]() {
    return ++count; // Compilation error
};
```

Adding `mutable` allows the closure object to modify its captured state.

```cpp
int count = 0;

auto counter = [count]() mutable {
    return ++count;
};

counter(); // 1
counter(); // 2
counter(); // 3

// Original count is still 0
```

Conceptually, the compiler-generated call operator changes from:

```cpp
// Without mutable
int operator()() const;

// With mutable
int operator()();
```

**Important:** `mutable` modifies the captured copy inside the closure object, not the original variable.

A lambda that captures a non-const variable by reference can modify the original variable without `mutable`.

```cpp
int count = 0;

auto increment = [&count]() {
    return ++count;
};

increment(); // 1
increment(); // 2

// Original count is now 2
```

---

## 5. Copying a Mutable Lambda

A mutable lambda can maintain internal state across calls.

When copied, the new closure object receives a copy of the captured state at that moment.

```cpp
auto a = [n = 0]() mutable {
    return ++n;
};

a(); // 1
a(); // 2

auto b = a; // Copies current state (n = 2)

a(); // 3
b(); // 3
b(); // 4
a(); // 4
```

Both objects have the same closure type, but their captured states evolve independently.

**Key distinction:**
- Copying the lambda creates another closure object.
- Its value-captured state is copied.
- Calling either object updates only its own state in this example.

Reference-captured variables, however, may still refer to the same external state after copying.

---

## 6. Captures and Closure Object Size

Captured variables can contribute to the size of a closure object.

```cpp
#include <iostream>

int main() {
    int a = 10;
    double b = 20.5;

    auto empty = [] {};
    auto one   = [a] {};
    auto two   = [a, b] {};

    std::cout << sizeof(empty) << '\n';
    std::cout << sizeof(one) << '\n';
    std::cout << sizeof(two) << '\n';
}
```

The exact sizes depend on the compiler, alignment, padding, and capture representation.

An empty closure object also has a nonzero size.

---

## 7. Why Does This Matter for Performance?

Closure objects have concrete types known at compile time.

This gives compilers opportunities to optimize lambda usage.

### 7.1 Inline `operator()` Calls

Inlining replaces a function call with its actual implementation.

```cpp
auto square = [](int x) {
    return x * x;
};

int result = square(5);
```

Instead of performing a separate call to `operator()`, the compiler may effectively transform the expression into:

```cpp
int result = 5 * 5;
```

And potentially simplify it further:

```cpp
int result = 25;
```

**Benefit:** Potentially avoids function-call overhead and enables additional optimizations.

Inlining is not guaranteed and is not exclusive to lambdas.

### 7.2 Optimize Captured State

```cpp
int factor = 10;

auto multiply = [factor](int x) {
    return x * factor;
};

int result = multiply(5);
```

Because the compiler can see the captured value and the call, it may simplify the calculation to:

```cpp
int result = 50;
```

This is an example of **constant propagation and constant folding**.

**Benefit:** Potentially reduces memory accesses and runtime computations.

### 7.3 Eliminate Unnecessary Objects

```cpp
auto calculate = [factor = 10](int x) {
    return x * factor;
};

int result = calculate(5);
```

Conceptually, the lambda creates a closure object storing `factor`.

However, if the compiler can prove that the object isn't needed in the generated machine code, the result may be equivalent to:

```cpp
int result = 50;
```

**Benefit:** The compiler may avoid materializing the closure object and accessing its stored state.

A lambda object does not inherently require heap allocation.

### 7.4 Avoid Type-Erasure Overhead

Consider a direct lambda:

```cpp
auto multiply = [factor = 10](int x) {
    return x * factor;
};

int result = multiply(5);
```

The compiler knows the exact closure type, making direct calls and inlining possible.

Now compare it with `std::function`:

```cpp
#include <functional>

std::function<int(int)> multiply =
    [factor = 10](int x) {
        return x * factor;
    };

int result = multiply(5);
```

`std::function` hides the concrete callable type behind a common interface, a technique called **type erasure**.

Depending on the implementation and optimization context, it may introduce:

- Additional call indirection.
- Callable storage and management overhead.
- Possible heap allocation for larger callables.
- Reduced opportunities for inlining.

**Benefit:** Using concrete lambda types directly, or passing them through templates, avoids introducing type-erasure overhead.

However, optimized `std::function` calls can sometimes have their overhead removed as well.

---

## 8. Key Takeaways

| Concept | Explanation |
|---|---|
| Closure type | Unique, unnamed type associated with each lambda expression |
| Closure object | Instance created when a lambda expression is evaluated |
| Multiple calls | Reuse the same object without creating another |
| Multiple objects | Can share one closure type while maintaining independent value-captured state |
| Value capture | Stores a copy of the captured value |
| Reference capture | Allows access to the original variable |
| `mutable` | Removes the implicit `const` from the lambda's call operator |
| Copying a lambda | Copies its captured state according to member copy semantics |
| Performance | Concrete closure types enable potential inlining and other compiler optimizations |

**One lambda expression → One unique closure type → Potentially many objects → Unlimited calls.**

Lambdas are not automatically faster than ordinary functions or functors. Their advantage is that they naturally integrate with C++'s static type system, templates, and compile-time optimizations.

Understanding closure objects helps us reason about captured state, object lifetimes, copies, and performance-sensitive C++ code.

---

**Next: Day 44 — `std::optional`: Handling Missing Values Safely**

#BeyondTheKernel #ModernCpp #Cpp17 #SoftwareEngineering #PerformanceEngineering #LowLatency
