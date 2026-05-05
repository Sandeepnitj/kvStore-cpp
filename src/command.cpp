#include "../include/command.h"
#include "../include/response.h"

#include <iostream>

using namespace std;

// SET
void SetCommand::execute(Store &store, const vector<string> &args)
{
    if(args.size() < 3)
    {
        cout << Response::error("SET requires key and value") << endl;
        return;
    }

    string key = args[1];
    string value = args[2];

    // Join remaining tokens as value
    int i = 3;
    while (i < args.size() && args[i] != "EX")
    {
        value += " " + args[i];
        i++;
    }

    long long ttl = -1;

    // Check for EX
    if(i < args.size() && args[i] == "EX")
    {
        if(i+1 >= args.size())
        {
            cout << Response::error("EX requires seconds") << endl;
            return;
        }

        ttl = stoll(args[i + 1]);
    }

    store.set(key, value, ttl);

    cout << Response::ok() << endl;
}

// GET
void GetCommand::execute(Store &store, const vector<string> &args)
{
    if(args.size() != 2)
    {
        cout << Response::error("Error: GET requires 1 argument (key)") << endl;
        return;
    }

    cout << Response::value(store.get(args[1])) << endl;
}

// DEL
void DelCommand::execute(Store &store, const vector<string> &args)
{
    if(args.size() != 2)
    {
        cout << Response::error("Error: DEL requires 1 argument (key)") << endl;
        return;
    }

    store.del(args[1]);

    cout << Response::ok() << endl;
}

// HELP
void HelpCommand::execute(Store& store, const vector<string> &args)
{
    cout << "Available commands:" << endl;
    cout << "  SET  <key> <value> [EX seconds]  - Store value with optional expiry" << endl;
    cout << "  GET  <key>                       - Retrieve value" << endl;
    cout << "  DEL  <key>                       - Delete key" << endl;
    cout << "  HELP                             - Show commands" << endl;
    cout << "  EXIT                             - Quit program" << endl;
    cout << "\n  Cache capacity: " << store.getCapacity() << " (LRU eviction)" << endl;
}