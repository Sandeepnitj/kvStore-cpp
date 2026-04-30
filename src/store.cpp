#include "store.h"

using namespace std;

void Store::set(const string &key, const string &value)
{
    db[key] = value;
}

string Store::get(const string &key)
{
    if(db.find(key) != db.end())
    {
        return db[key];
    }
    return "NULL";
}

void Store:: del(const string &key)
{
    db.erase(key);
}