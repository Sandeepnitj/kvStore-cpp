#include <iostream>
#include <vector>
#include "store.h"
#include "parser.h"

using namespace std;

int main()
{
    Store store;
    string line;

    cout << "KV Store Started (Type EXIT to quit)" << endl;

    while(true)
    {
        cout << "> ";
        getline(cin, line);

        if(line == "EXIT")  break;

        vector<string> tokens = Parser::parse(line);

        if(tokens.empty())  continue;

        string command = tokens[0];

        if(command == "SET")
        {
            if(tokens.size() < 3)
            {
                cout << "Usage: SET key value" << endl;
                continue;
            }

            string key = tokens[1];

            // Join remaining tokens as value
            string value = tokens[2];

            for(int i = 3; i < tokens.size(); i++)
            {
                value += " " + tokens[i];
            }

            store.set(key, value);

            cout << "OK" << endl;
        }
        else if(command == "GET")
        {
            if (tokens.size() != 2)
            {
                cout << "Usage: GET key" << endl;
                continue;
            }

            cout << store.get(tokens[1]) << endl;
        }
        else if(command == "DEL")
        {
            if(tokens.size() != 2)
            {
                cout << "Usage: DEL key" << endl;
                continue;
            }

            store.del(tokens[1]);

            cout << "Deleted" << endl;
        }
        else
        {
            cout << "Invalid Command" << endl;
        }
    }

    return 0;
}