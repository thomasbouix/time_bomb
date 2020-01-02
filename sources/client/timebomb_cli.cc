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

void error(std::string message){
	std::cout << message << std::endl;
	exit(1);
}

void serveur_tcp(int port,std::string name)
{
        int sockfd, cli_sockfd,read_n;
        socklen_t cli_len;
        struct sockaddr_in serv_addr, cli_addr;
	char buffer[1024];

        sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sockfd<0) error("[-]Error in connection");

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port);

       	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("[-]Error in binding.");

        listen(sockfd,5);
        cli_len = sizeof(cli_addr);
        while (1)
        {
                cli_sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
                if (cli_sockfd < 0) error("[-]Error in accepting");
                read_n = read(cli_sockfd,buffer,1024);
                if (read_n < 0) error("[-]Error in reading data");

		std::string str(buffer);
		if(str.size() > 0 ){

			std::cout << "\r" << str << "\n" <<name << ": ";
			bzero(buffer, sizeof(buffer));
		}
     	}
}

void client_tcp(std::string server_ip, int server_port, std::string name,std::string message){

	int client_socket, ret;
	struct sockaddr_in server_addr;
	std::string buffer;

	client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(client_socket < 0) error("[-]Error in connection");

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(server_port);
	server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());

	ret = connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(ret < 0) error("[-]Error in connection");

	send(client_socket, (char*)(message.c_str()), message.size(), 0);

	while(1){
		std::cout << "\r" << name << ": ";
   		std::getline(std::cin, buffer,'\n');
		write(client_socket,buffer.c_str(),buffer.size());
		//if(buffer.size() > 0)
			//send(client_socket,(char*)(buffer.c_str()), buffer.size(), 0);
	}

}


int main(){
	std::string server_ip,client_ip,name;
	int server_port,client_port;
	server_ip = "127.0.0.1";
	client_ip = "127.0.0.1";
	//std::cout << "Adresse IP Serveur:";
	//std::cin >> server_ip;
	std::cout << "Numéro de Port Serveur:";
	std::cin >> server_port;
	//std::cout << "Adresse IP Client:";
	//std::cin >> client_ip;
	std::cout << "Numéro de Port Client:";
	std::cin >> client_port;
	std::cout << "Entrez votre nom:";
	std::cin >> name;

	std::stringstream message;
	message << client_ip << "\n" << client_port << "\n" << name << "\n";
	std::thread thread_serv(serveur_tcp,client_port,name);
	thread_serv.detach();
	std::thread thread_cli(client_tcp,server_ip,server_port,name,message.str());
	thread_cli.detach();

	while(1);

	return 0;
}

