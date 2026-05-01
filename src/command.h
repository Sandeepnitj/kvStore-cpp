#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>
#include "store.h"

class Command
{
public:
    virtual void execute(Store &store, const std::vector<std::string> &args) = 0;
    virtual ~Command() {}
};

//SET
class SetCommand : public Command
{
public:
    void execute(Store &store, const std::vector<std::string> &args) override;
};

//GET
class GetCommand : public Command
{
public:
    void execute(Store &store, const std::vector<std::string> &args) override;
};

//DEL
class DelCommand : public Command
{
public:
    void execute(Store &store, const std::vector<std::string> &args) override;
};

// HELP
class HelpCommand : public Command
{
public:
    void execute(Store& store, const std::vector<std::string>& args) override;
};

#endif