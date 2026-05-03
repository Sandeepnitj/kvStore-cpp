# KV Store (C++) — Redis-like In-Memory Key-Value Store

A high-performance in-memory key-value store built from scratch in C++, inspired by Redis.

This project demonstrates system design concepts like command parsing, modular architecture, memory safety, and TTL-based expiration.

---

## Features

* **SET key value** → Store a value
* **GET key** → Retrieve a value
* **DEL key** → Delete a key
* **TTL Support** → Expiry using `EX seconds`
* **Command Pattern** → Clean, extensible design
* **Smart Pointers** → Memory-safe implementation
* **Response System** → Standardized outputs
* **HELP Command** → Built-in command guide

---

## Example Usage

```
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

* **Store** → Handles data storage and TTL logic
* **Parser** → Parses user input
* **Command Pattern** → Executes commands
* **Response Layer** → Standardizes output

---

## Project Structure

```
kvstore-cpp/
├── src/
│   ├── main.cpp
│   ├── store.cpp / store.h
│   ├── parser.cpp / parser.h
│   ├── command.cpp / command.h
│   ├── response.cpp / response.h
```

---

## Build & Run

```bash
g++ -std=c++17 src/*.cpp -o kvstore
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
* Response abstraction (standardized output)

### Day 4

* TTL (expiry system) using lazy expiration
* Updated HELP command

---

## Key Concepts Implemented

* In-memory storage using `unordered_map`
* Lazy expiration (TTL)
* Command Pattern (extensible architecture)
* RAII & `unique_ptr` for memory safety
* CLI-based interaction

---

## Upcoming Features

* LRU Cache (memory eviction)
* Persistence (file storage)
* TCP Server (networking)
* Multithreading support

---

## Goal

To build a FAANG-level backend/system design project in C++ demonstrating real-world system concepts.

---