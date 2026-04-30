#ifndef STORE_H
#define STORE_H

#include <string>
#include <unordered_map>

using namespace std;

class Store
{
private:
    unordered_map<string, string> db;

public:
    void set(const string &key, const string &value);
    string get(const string &key);
    void del(const string &key);  
};

#endif