/*
 * Server.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Eli
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

#include <pthread.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "CLI.cpp"
#include "commands.h"

using namespace std;
class SocketIO: public DefaultIO{
   int userID;
public:
    SocketIO(int userID){
        this->userID = userID;
    }
    string read(){
        string serverInput="";
        char c=0;
        read(userID,&c,sizeof(char));
        while(c!='\n'){
            serverInput+=c;
            read(userID,&c,sizeof(char));
        }
        return serverInput;
    }

    void write(string text){
        write(userID,text,text.length());
        write(userID,"\n",1);
    }

    void write(float f){
        write(userID,to_string(f),to_string(f).length());
        write(userID,"\n",1);
    }

    void read(float *f){
        cin>>*f;
    }
};
// edit your ClientHandler interface here:
class ClientHandler{
public:
    virtual void handle(int clientID){

        /*
            char buffer[1024];
            int n = read(clientID,buffer,100);//input from user
            send(clientID,"hello\n",strlen("hello\n"),0);//write to user.
    */
    }
};


// you can add helper classes here and implement on the cpp file


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
public:
    virtual void handle(int clientID){
        SocketIO socketIo(clientID);
        CLI cli(&socketIo);
        cli.start();
        socketIo.close();
    }
};
struct sockaddr_in{
 unit8_t sin_len; //length of structure 1
 sa_family_t sin_family;//AF_INIT
 in_port_t sin_port;//16 bit port number
 struct in_addr sin_addr;//32 bit IPV4 address
 char sin_zero[8];
};

// implement on Server.cpp
class Server {
    thread* t; // the thread to run the start() method in
    int fd;
    sockaddr_in server;
    sockaddr_in client;
    bool stp;
    // you may add data members

public:
    Server(int port) throw (const char*);
    virtual ~Server();
    void start(ClientHandler& ch)throw(const char*);
    void stop();
};

#endif /* SERVER_H_ */
