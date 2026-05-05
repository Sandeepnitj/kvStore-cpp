# KV Store (C++) — Redis-like In-Memory Key-Value Store

A high-performance in-memory key-value store built from scratch in C++, inspired by Redis.

This project demonstrates core backend and system design concepts such as command parsing, modular architecture, caching strategies (TTL + LRU), and persistence.

---

## Features

* **SET key value** → Store a value
* **GET key** → Retrieve a value
* **DEL key** → Delete a key
* **TTL Support** → Expiry using `EX seconds`
* **LRU Cache** → Automatic eviction when capacity is exceeded
* **Command Pattern** → Clean, extensible architecture
* **Smart Pointers** → Memory-safe implementation
* **Response System** → Standardized outputs
* **Persistence** → Save and reload data from file
* **HELP Command** → Built-in command guide

---

## Example Usage

```text
> SET name Sandeep
OK

> GET name
Sandeep

> SET temp data EX 3
OK

> GET temp
data

(wait 3 seconds)

> GET temp
NULL
```

---

## Architecture

* **Store**

  * In-memory storage (`unordered_map`)
  * TTL (expiry handling)
  * LRU cache (eviction policy)

* **Parser**

  * Parses user input into tokens

* **Command Layer**

  * Implements Command Pattern (`SET`, `GET`, `DEL`, `HELP`)

* **Response Layer**

  * Standardized outputs (`OK`, `ERR`, values)

* **Persistence Layer**

  * Saves data to file and reloads on startup

---

## Project Structure

```text
kvstore-cpp/
├── src/            # Source files (.cpp)
│   ├── main.cpp
│   ├── store.cpp
│   ├── parser.cpp
│   ├── command.cpp
│   ├── response.cpp
│
├── include/        # Header files (.h)
│   ├── store.h
│   ├── parser.h
│   ├── command.h
│   ├── response.h
│
├── data/           # Persistence files
│   └── dump.txt
│
├── README.md
├── .gitignore
```

---

## Build & Run

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o kvstore
./kvstore
```

---

## Progress

### Day 1

* Basic key-value store (SET, GET, DEL)

### Day 2

* Command parser (support for spaces in values)

### Day 3

* Command Pattern implementation
* HELP command
* Smart pointers (memory safety)
* Response abstraction

### Day 4

* TTL (expiry system using lazy expiration)

### Day 5

* LRU cache (eviction policy)

### Day 6

* Persistence (save/load from file)
* Refactored project structure (`src/`, `include/`, `data/`)

---

## Key Concepts Implemented

* In-memory storage using `unordered_map`
* Lazy expiration (TTL)
* LRU cache (O(1) operations using list + hashmap)
* Command Pattern (extensible architecture)
* RAII and `unique_ptr` for memory safety
* File-based persistence
* Clean project structure

---

## Upcoming Features

* TCP Server (networking)
* Multithreading (handle multiple clients)
* Advanced persistence (append-only log)
* Configurable capacity

---

## Goal

To build a FAANG-level backend/system design project in C++ demonstrating real-world concepts like caching, persistence, networking, and concurrency.

---
