#include "../include/store.h"
#include "../include/parser.h"
#include "../include/command.h"

#include <unordered_map>
#include <memory>
#include <sstream>

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080

int main()
{
    int server_fd;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    // Initialize address
    memset(&address, 0, sizeof(address));

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("socket failed");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        return -1;
    }

    // Listen
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        return -1;
    }

    std::cout << "Server started on port " << PORT << std::endl;
    std::cout << "Waiting for client..." << std::endl;

    // Initialize Store
    Store store;
    store.loadFromFile();

    // Command map
    std::unordered_map<std::string, std::unique_ptr<Command>> commands;
    commands["SET"] = std::make_unique<SetCommand>();
    commands["GET"] = std::make_unique<GetCommand>();
    commands["DEL"] = std::make_unique<DelCommand>();
    commands["HELP"] = std::make_unique<HelpCommand>();

    // Server loop
    while (true)
    {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);

        if (new_socket < 0)
        {
            perror("accept");
            continue;
        }

        std::cout << "Client connected" << std::endl;

        char buffer[1024] = {0};
        int valread = read(new_socket, buffer, sizeof(buffer));

        if (valread <= 0)
        {
            close(new_socket);
            continue;
        }

        std::string input(buffer);

        // Remove newline
        if (!input.empty())
        {
            input.erase(input.find_last_not_of("\n\r") + 1);
        }

        std::vector<std::string> tokens = Parser::parse(input);
        std::string response;

        if (!tokens.empty())
        {
            std::string cmd = tokens[0];

            if (commands.find(cmd) != commands.end())
            {
                std::stringstream ss;
                std::streambuf *old = std::cout.rdbuf(ss.rdbuf());

                commands[cmd]->execute(store, tokens);

                std::cout.rdbuf(old);

                response = ss.str();
            }
            else
            {
                response = "ERR Invalid command\n";
            }
        }
        else
        {
            response = "ERR Empty command\n";
        }

        // Send response
        send(new_socket, response.c_str(), response.size(), 0);

        close(new_socket);
    }

    return 0;
}