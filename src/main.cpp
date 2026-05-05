#include <iostream>
#include <memory>
#include <unordered_map>

#include "store.h"
#include "parser.h"
#include "command.h"
#include "response.h"

using namespace std;

int main()
{
    Store store;
    string line;

    // Load from File
    store.loadFromFile();

    // Command registry
    unordered_map<string, unique_ptr<Command>> commands;

    // Using Smart pointers to initialize commands objects
    commands["SET"] = make_unique<SetCommand>();
    commands["GET"] = make_unique<GetCommand>();
    commands["DEL"] = make_unique<DelCommand>();
    commands["HELP"] = make_unique<HelpCommand>();

    cout << "KV Store Started. Type HELP for commands." << endl;

    while(true)
    {
        cout << "> ";
        getline(cin, line);

        if(line == "EXIT")  break;

        vector<string> tokens = Parser::parse(line);

        // Continue if empty
        if(tokens.empty())  continue;

        string cmd = tokens[0];

        // Execute Command
        if(commands.find(cmd) != commands.end())
        {
            commands[cmd]->execute(store, tokens);
        }
        else
        {
            cout << Response::error("Invalid command") << endl;
        }
    }

    return 0;
}