#include "command.h"
#include "response.h"

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

    // Join remaining tokens as value
    string value = args[2];

    for(int i = 3; i < args.size(); i++)
    {
        value += " " + args[i];
    }

    store.set(key, value);

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
    cout << "Available commands:"                     << endl;
    cout << "  SET  <key> <value>  - Store a value"   << endl;
    cout << "  GET  <key>          - Retrieve value"  << endl;
    cout << "  DEL  <key>          - Delete key"      << endl;
    cout << "  HELP                - Show commands"   << endl;
    cout << "  EXIT                - Quit program"    << endl;
}