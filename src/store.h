#ifndef STORE_H
#define STORE_H

#include <string>
#include <unordered_map>

class Store
{
private:
    std::unordered_map<std::string, std::string> db;

public:
    void set(const std::string &key, const std::string &value);
    std::string get(const std::string &key);
    void del(const std::string &key);
};

#endif