# Beyond the Kernel | Modern C++ & Linux | Day 1 — epoll

## Topic
Understanding how Linux handles thousands of network connections efficiently using epoll.

## Key idea
Instead of scanning every file descriptor repeatedly, epoll lets the kernel notify us only when a file descriptor is ready for I/O.

## What this covers
- File descriptors
- epoll
- epoll_create1
- epoll_ctl
- epoll_wait

## Goal
Build a minimal TCP server using epoll and a TCP multi client.
