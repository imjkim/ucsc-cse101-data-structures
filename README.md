# CSE 101 — Introduction to Data Structures and Algorithms (UC Santa Cruz)

Coursework from UC Santa Cruz's core algorithms course (**2020**), written in **C**, with one assignment in **C++**.
Each assignment builds a reusable ADT (abstract data type) and a client program that uses it on real input files. Later assignments reuse earlier ones: the List ADT from pa1 is the base for BigInteger and both Graph assignments.

> **About the dates:** this repo was put on GitHub in 2026, but the commit history was rebuilt from the original file timestamps.
> Each commit is dated when those files were last saved. A few files date from spring 2020, and two pa1 commits from 2024 are when I came back to tidy up the List ADT.

## What's inside

| Folder | ADT / client | What it does | Key algorithms & concepts |
|---|---|---|---|
| [`pa1`](pa1) | **List** (doubly linked list with a cursor) · `Lex` | Sorts the lines of a file alphabetically by insertion-sorting a List of *indices*, without moving the strings | Doubly linked lists, cursor-based iteration, indirect sorting |
| [`pa2`](pa2) | **BigInteger** · `Arithmetic` | Arbitrary-precision signed integers stored as base 10⁹ digits in a List; computes A+B, A−B, A×B, A², and similar expressions | Bignum arithmetic, carry/borrow normalization |
| [`pa3`](pa3) | **Graph** (adjacency lists) · `FindPath` | Reads a graph and answers shortest-path queries between vertex pairs | Breadth-first search, shortest paths, path reconstruction |
| [`pa4`](pa4) | **Graph** (directed) · `FindComponents` | Finds the strongly connected components of a directed graph | Depth-first search, discover/finish times, transpose graph, Kosaraju-style SCC |
| [`pa5`](pa5) | **List** in C++ · `Shuffle` | Counts how many perfect riffle shuffles bring a deck of n cards back to its original order | C++ classes, constructors/destructors, operator overloading, Rule of Three |
| [`pa6`](pa6) | **Dictionary** (binary search tree) · `Lex` | Sorts the lines of a file using a BST-backed dictionary | BST insert/delete/search, in-order traversal |
| [`pa7`](pa7) | **Dictionary** (red-black tree) · `Order` | Balanced dictionary; prints keys in pre-, in-, and post-order | Red-black tree insertion fix-up, rotations, sentinel `nil` node |

## Building and running

Each folder has its own Makefile (Linux, macOS, or WSL with `gcc`/`g++` and `make`):

```bash
cd pa3
make
./FindPath in1 out1      # input: a graph plus source/destination query pairs
make clean
```

`pa1` uses `Makefile.txt`, so build it with `make -f Makefile.txt`.

Each assignment includes a unit-test driver (`ListTest`, `GraphTest`, `DictionaryTest`, …) that I used to test the ADT on its own, separate from the client program. Memory use was checked with Valgrind.

## Tech
C (C99) · C++11 · GCC / G++ · GNU Make · Valgrind

## Notes
- Interface headers and some test clients were provided by the course. The implementations are my own.
- These are student assignments, shared as part of my portfolio. If you're taking CSE 101 now, please follow your course's academic integrity policy.
