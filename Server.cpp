
#include "Server.h"

Server::Server(int port)throw (const char*) {
        fd = socket(AF_INET, SOCK_STREAM,0);
        if (fd<0){
            throw "socket failed";
        }
        server.sin_family = AF_INIT;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(port);

        if (bind(fd,(struct sockaddr*)&server,sizeof(server))<0){
            throw "bind failued";
        }
        if(listen(fd,3)<0){
            throw "listen failed";
        };
        stp = 0;
}

void Server::start(ClientHandler& ch)throw(const char*){
    while (not stp) {
        t = new thread([&ch, this]() {
            socklen_t clientSize = sizeof(client);
            int aCLient = accept(fd, (struct sockaddr *) &client, &clientSize);
            if (aCLient < 0)throw "accept failed";
            ch.handle(aCLient);
            close(aCLient);
            //close(fd);
        });
        close(fd);
    }
}

void Server::stop(){
    t->join(); // do not delete this!
    stp = 1;
}

Server::~Server() {
}

