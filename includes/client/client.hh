#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include "picture.hh"
#include "text.hh"
#include "window.hh"

extern std::string global_buffer_write;
extern std::string global_buffer_read;

extern volatile int synchro_write;
extern volatile int synchro_read;

class Client{

  private:
    std::string name;
    std::string ip;
    int port;
    std::string server_ip;
    int server_port;

  public:
    Client(std::string name, int client_port, int server_port,std::string client_ip, std::string server_ip);
    ~Client();

    //void serveur_tcp(int port,std::string name);
    //void client_tcp(std::string server_ip, int server_port, std::string name,std::string message);
    //void error(std::string message);
};
