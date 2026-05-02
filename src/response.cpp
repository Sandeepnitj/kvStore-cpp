#include "response.h"

using namespace std;

string Response::ok()
{
    return "OK";
}

string Response::error(const std::string &msg)
{
    return "ERR " + msg;
}

string Response::value(const std::string &val)
{
    return val;
}