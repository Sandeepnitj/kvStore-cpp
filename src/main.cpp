#include <iostream>
#include <unordered_map>

#include "store.h"
#include "parser.h"
#include "command.h"

using namespace std;

int main()
{
    Store store;
    string line;

    // Command registry
    unordered_map<string, Command*> commands;
    commands["SET"] = new SetCommand();
    commands["GET"] = new GetCommand();
    commands["DEL"] = new DelCommand();
    commands["HELP"] = new HelpCommand();

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
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}