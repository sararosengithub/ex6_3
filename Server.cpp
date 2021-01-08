
#include "Server.h"
#include <chrono>

Server::Server(int port) throw(const char *)
{
    fd = socket(AF_INET, SOCK_STREAM, 0); //const can be field in h
    if (fd < 0)
    {
        throw "socket failed";
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (bind(fd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        throw "bind failed";
    }
    if (listen(fd, 3) < 0)
    {
        throw "listen failed";
    }
    stp = 0;
}

void Server::start(ClientHandler &ch) throw(const char *)
{

    t = new thread([&ch, this]() {
        while (!stp)
        {
            socklen_t clientSize = sizeof(this->client);
            cout << clientSize << endl;
            int aCLient = accept(fd, (struct sockaddr *)&client, &clientSize);
            if (aCLient < 0)
                throw "accept failed";
            else
                cout << "client accepted succesfully" << endl;
            ch.handle(aCLient);
            close(aCLient);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        close(fd);
    });
    //close(fd);
}

void Server::stop()
{
    stp = 1;
    t->join(); // do not delete this!
}

Server::~Server()
{
}
