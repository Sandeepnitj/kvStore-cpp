# KV Store (C++)

A simple in-memory key-value store supporting:

- SET key value
- GET key
- DEL key
- HELP
- EXIT

## Run

g++ -std=c++17 src/main.cpp src/store.cpp src/parser.cpp src/command.cpp -o kvStore

./kvstore