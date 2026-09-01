# Beyond the Kernel | Modern C++ & Linux | Day 28 - mmap() Has More Tricks

On Day 27, we used `mmap()` to ask Linux for **anonymous memory**.

But `mmap()` has a few more tricks up its sleeve.

It can also:

- Map a file into virtual memory

- Create private mappings using **Copy-on-Write**

- Create shared mappings between processes

- Map certain device or special memory regions

## A Simple Way to Think About It

```text
mmap()
  |
  |---- Anonymous Memory
  |
  |---- File Mapping
  |
  |---- Shared Memory
  |
  |---- Device / Special Memory
```

And this is where earlier topics start connecting:

- **Demand Paging** → mapped pages can be brought in as needed

- **Copy-on-Write** → `MAP_PRIVATE`

- **Shared Memory** → `MAP_SHARED`

- **Device Mapping** → lets user-space programs access device or driver-exposed memory regions through mapped addresses

So `mmap()` is less:

> "map a file"

and more:

> **"create a virtual-memory mapping and decide what backs it."**

Next: **Shared Memory** — when two processes intentionally work with the same underlying memory.
