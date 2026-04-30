#include <iostream>
#include "store.h"

using namespace std;

int main()
{
    Store store;
    string command, key, value;

    cout << "Simple Key-Value Store Started. Type commands: " << endl;

    while(true)
    {
        cout << "> ";
        cin >> command;

        if(command == "SET")
        {
            cin >> key >> value;

            store.set(key, value);

            cout << "OK" << endl;
        }
        else if(command == "GET")
        {
            cin >> key;

            cout << store.get(key) << endl;
        }
        else if(command == "DEL")
        {
            cin >> key;

            store.del(key);

            cout << "Deleted" << endl;
        }
        else if(command == "EXIT")
        {
            break;
        }
        else
        {
            cout << "Invalid Command" << endl;
        }
    }

    return 0;
}