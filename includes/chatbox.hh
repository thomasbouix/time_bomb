#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <vector>
#include <thread>
#include <sstream>
#include <algorithm>
#include "client.hh"

extern std::string global_buffer;
extern std::vector<Client *> clients;

class Chatbox
{
  private:
    int port,number_players;
    int sockfd;

  public:
    Chatbox(int port, int number_players);
    void print_clients();
    void broadcast_message(std::string message);
    std::vector<std::string> get_name_players();
    ~Chatbox();

};
