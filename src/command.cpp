#include "command.h"
#include <iostream>

using namespace std;

// SET
void SetCommand::execute(Store &store, const vector<string> &args)
{
    if(args.size() < 3)
    {
        cout << "Error: SET requires key and value" << endl;
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

    cout << "OK" << endl;
}

// GET
void GetCommand::execute(Store &store, const vector<string> &args)
{
    if(args.size() != 2)
    {
        cout << "Error: GET requires 1 argument (key)" << endl;
        return;
    }

    cout << store.get(args[1]) << endl;
}

// DEL
void DelCommand::execute(Store &store, const vector<string> &args)
{
    if(args.size() != 2)
    {
        cout << "Error: DEL requires 1 argument (key)" << endl;
        return;
    }

    store.del(args[1]);

    cout << "Deleted" << endl;
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