#include "store.h"
#include <chrono>

using namespace std;

long long getCurrentTime()
{
    return chrono::duration_cast<chrono::seconds>(
        chrono::system_clock::now().time_since_epoch()
    ).count();
}

void Store::set(const string &key, const string &value, long long ttl)
{
    Entry entry;
    entry.value = value;

    if (ttl == -1)
    {
        entry.expiryTime = -1;
    }
    else
    {
        entry.expiryTime = getCurrentTime() + ttl;
    }

    db[key] = entry;
}

std::string Store::get(const std::string &key)
{
    if (db.find(key) == db.end())
    {
        return "NULL";
    }

    Entry &entry = db[key];

    // Check expiry
    if (entry.expiryTime != -1 && getCurrentTime() > entry.expiryTime)
    {
        db.erase(key);
        return "NULL";
    }

    return entry.value;
}

void Store:: del(const string &key)
{
    db.erase(key);
}