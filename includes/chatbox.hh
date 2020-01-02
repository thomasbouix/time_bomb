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
		~Chatbox();

		void print_clients();
		static void send_message(int server_port, std::string server_ip, std::string message);
		void broadcast_message(std::string message);
		std::vector<std::string> get_name_players();

		std::string get_ip_client(std::string client_name);
		int get_port_client(std::string client_name);

};
