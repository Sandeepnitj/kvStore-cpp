#include "../include/store.h"

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
    long long expiry = (ttl == -1) ? -1 : getCurrentTime() + ttl;

    auto it = db.find(key);

    // If key exists → update + move to front
    if(it != db.end())
    {
        lruList.erase(it->second.lruIt);
    }

    // Insert at front (most recently used)
    lruList.push_front(key);

    Entry entry;
    entry.value = value;
    entry.expiryTime = expiry;
    entry.lruIt = lruList.begin();

    db[key] = entry;

    // Evict if over capacity
    if(db.size() > capacity)
    {
        string lruKey = lruList.back();
        lruList.pop_back();
        db.erase(lruKey);
    }

    // Save to File
    saveToFile();
}

std::string Store::get(const std::string &key)
{
    auto it = db.find(key);

    if (it == db.end())
    {
        return "NULL";
    }

    Entry &entry = it->second;

    // Check TTL expiry
    if (entry.expiryTime != -1 && getCurrentTime() > entry.expiryTime)
    {
        lruList.erase(entry.lruIt);
        db.erase(it);
        return "NULL";
    }

    // Move key to front (most recently used)
    lruList.erase(entry.lruIt);
    lruList.push_front(key);
    entry.lruIt = lruList.begin();

    return entry.value;
}

void Store::del(const string &key)
{
    auto it = db.find(key);

    if(it != db.end())
    {
        lruList.erase(it->second.lruIt);
        db.erase(it);
    }

    // Save to File
    saveToFile();
}

void Store::saveToFile()
{
    ofstream out(filename);

    for(auto &pair : db)
    {
        const string &key = pair.first;
        const Entry &entry = pair.second;

        out << key << " " << entry.value << " " << entry.expiryTime << endl;
    }

    out.close();
}

void Store::loadFromFile()
{
    ifstream in(filename);

    if(! in.is_open())
    {
        return;
    }

    string key, value;
    long long expiry;

    while( in >> key >> value >> expiry )
    {
        Entry entry;
        entry.value = value;
        entry.expiryTime = expiry;

        // Insert into LRU
        lruList.push_front(key);
        entry.lruIt = lruList.begin();

        db[key] = entry;
    }

    in.close();
}

size_t Store::getCapacity() const
{
    return capacity;
}