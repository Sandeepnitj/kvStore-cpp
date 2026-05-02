# KV Store (C++)

A simple in-memory key-value store supporting:

- SET key value
- GET key
- DEL key
- HELP
- EXIT

## Run

g++ -std=c++17 src/command.cpp src/main.cpp src/parser.cpp src/response.cpp src/store.cpp -o kvStore

./kvStore