#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

class Response
{
public:
    static std::string ok();
    static std::string error(const std::string &msg);
    static std::string value(const std::string &val);
};

#endif