#include "../includes/chatbox.hh"


std::vector<Client *> clients;

void error(std::string message){
	std::cout << message << std::endl;
	exit(1);
}

void send_message(int server_port, std::string server_ip, std::string message){

	int client_socket, ret, n;
	struct sockaddr_in server_addr;
	std::string buffer,name;

	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(client_socket < 0) error("[-]Error in connection");

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(server_port);
	server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());

	ret = connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(ret < 0) error("[-]Error in connection"); // ERREUR ICI
	n = write(client_socket,message.c_str(),message.size());
  if (n < 0) error("ERROR writing to socket");

}

void fn_serveur_tcp(int cli_sockfd, std::string name){
	char buffer[1024];
	while(1){
		if(recv(cli_sockfd,buffer, 1024, 0) > 0){
			std::string str(buffer);
			for(auto& x : clients){
				if(name != ((*x).get_name())) send_message((*x).get_port(),(*x).get_ip(),name + ":" + str);
			}
			global_buffer = global_buffer + name + ": " + str + "\n";
			bzero(buffer, sizeof(buffer));
		}
	}
	close(cli_sockfd);
}

Chatbox::Chatbox(int port, int number_players):port(port),number_players(number_players){

	int number_connect = 0;
  struct sockaddr_in server_addr;
  struct sockaddr_in new_addr;
  int new_socket;
  socklen_t addr_size;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) error("[-]Error in connection.");
	std::cout << "[+]Server Socket is created." << std::endl;

  memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  int ret = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(ret < 0) error("[-]Error in binding.");
  std::cout << "[+]Bind to port " << port << std::endl;

  if(listen(sockfd, 10) == 0) std::cout << "[+]Listening...." << std::endl;

  while(number_connect != number_players){
	  new_socket = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
	  if(new_socket < 0) error("[-]Error in accepting");

	  char buffer[255];
	  bzero(buffer, sizeof(buffer));

	  while(recv(new_socket,buffer, 255, 0) < 0) bzero(buffer, sizeof(buffer));

		std::string s(buffer);
	  std::stringstream ss(s);
	  std::vector<std::string> tab;
	  while ( std::getline(ss,s,'\n') ) tab.push_back(s);

		Client* client = new Client(tab[0],atoi(tab[1].c_str()),tab[2]);
	  clients.push_back(client);

	  std::thread thread_cli(fn_serveur_tcp,new_socket,tab[2]);
	  thread_cli.detach();
	  number_connect++;
	}
}

std::vector<std::string> Chatbox::get_name_players(){
	std::vector<std::string> players;
	for(auto& x : clients)
		players.push_back((*x).get_name());
	return players;
}

Chatbox::~Chatbox(){
	close(sockfd);
}

void Chatbox::print_clients(){
	for(auto& x : clients)
  	std::cout << "Nom: " << (*x).get_name() << "\tIp: " << (*x).get_ip() << "\tPort: " << (*x).get_port() << std::endl;
}

void Chatbox::broadcast_message(std::string message){
	for(auto& x : clients){
  //	if((*x).get_name() == (*x).get_name()) SI je met ça, ça me met que c'est une erreur de bind du client
			send_message((*x).get_port(),(*x).get_ip(),message);
	}
}
