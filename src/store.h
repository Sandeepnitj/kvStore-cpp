#ifndef STORE_H
#define STORE_H

#include <string>
#include <unordered_map>

struct Entry
{
    std::string value;
    long long expiryTime; // -1 means no expiry
};

class Store
{
private:
    std::unordered_map<std::string, Entry> db;

public:
    void set(const std::string &key, const std::string &value, long long ttl = -1);
    std::string get(const std::string &key);
    void del(const std::string &key);
};

#endif