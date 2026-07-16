# Beyond the Kernel | Modern C++ & Linux | Day 14 - Linux Process Memory Layout - Understanding `.text`, `.data`, `.bss`, `.rodata`, Heap and Stack

In the last few posts, we focused on Modern C++ features and writing efficient code.

Over the next few posts, let's shift our focus to Linux internals.

Every C++ program runs inside a Linux process, and understanding how that process is organized in memory is an important step toward writing high-performance software.

Let's understand this with an example:

```cpp
int my_global_initialized_data = 10;

int my_global_uninitialized_bss;

const char* my_global_message_rodata = "Beyond the Kernel";

int main()
{
    int my_local_stack_variable = 14;

    int* my_local_heap_variable = new int(14);

    delete my_local_heap_variable;
}
```

So where does everything live?

```text
.text
│
├── Compiled machine instructions

.data
│
├── my_global_initialized_data

.bss
│
├── my_global_uninitialized_bss

.rodata
│
├── "Beyond the Kernel"

Heap
│
├── *my_local_heap_variable

Stack
│
└── my_local_stack_variable
    my_local_heap_variable
    (The pointer itself lives on the stack,
     while the dynamically allocated integer lives on the heap.)
```

Let's briefly understand each region:

- **`.text`** → Contains the compiled machine instructions of your program.
- **`.data`** → Stores initialized global and static variables.
- **`.bss`** → Stores uninitialized or zero-initialized global and static variables.
- **`.rodata`** → Stores read-only data such as string literals.
- **Heap** → Memory allocated dynamically during runtime using `new`, `malloc()`, etc.
- **Stack** → Stores local variables, function parameters, and return information for function calls.

Every time your program starts, the operating system creates this virtual memory layout for the process.

Understanding where your data lives is often the first step toward understanding performance, memory usage, and object lifetime.

---

## Conclusion

- Every C++ program runs inside a Linux process with a well-defined memory layout.
- Different types of data are placed in different memory regions.
- Knowing where your objects live helps you understand performance, lifetime, and memory management.

In the next post, we will take a deeper look at two of the most important regions, **the Stack and the Heap**.
