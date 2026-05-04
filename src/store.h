#ifndef STORE_H
#define STORE_H

#include <string>
#include <list>
#include <unordered_map>

class Store
{
private:
    struct Entry
    {
        std::string value;
        long long expiryTime; // -1 means no expiry
        std::list<std::string>::iterator lruIt;
    };

    std::unordered_map<std::string, Entry> db;

    std::list<std::string> lruList;
    size_t capacity = 3;

public:
    void set(const std::string &key, const std::string &value, long long ttl = -1);
    std::string get(const std::string &key);
    void del(const std::string &key);

    size_t getCapacity() const;
};

#endif