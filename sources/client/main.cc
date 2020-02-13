#include <iostream>
#include <vector>
#include <unistd.h>
#include "../../includes/client/game.hh"
/*
int main(void){

  Color color(174,100,56);

  Window* ma_fenetre = new Window("TimeBomb",1024,768,color);
  Picture* image = new Picture("fond.png",1024,768,0,0);
  Picture* image2 = new Picture("chat.png",485, 490, 525, 265);
  Picture* image3 = new Picture("red.png",100, 200,30, 500);
  (*ma_fenetre).add(image);
  (*ma_fenetre).add(image2);
  (*ma_fenetre).add(image3);

  (*ma_fenetre).add_text("Round played:",30,290);
  (*ma_fenetre).add_text("Cards drew in this round:",30,330);
  (*ma_fenetre).add_text("Number of defusers found:",30,370);

  for(int i=0; i<27; i++)
    (*ma_fenetre).add_chat(" ",535,275+16*i);

  (*ma_fenetre).add_line("wsh la cite1");


  (*ma_fenetre).display();


  delete ma_fenetre;

  return 0;
}
*/

int main(int argc, char * argv[]){

	// <server ip> <server port> <client ip> <client port> <name>

	if (argc != 4) {
		std::cout << "error in arguments : " << std::endl;
		std::cout << "<server port> <client port> <name>" << std::endl;
		exit(0);
	}

	std::string server_ip,client_ip;
	int server_port,client_port;
	std::string str_serv(argv[1]);
	std::string str_cli(argv[2]);
	std::string name(argv[3]);

	server_port = std::stoi(str_serv);
	client_port = std::stoi(str_cli);
	server_ip = "127.0.0.1";
	client_ip = "127.0.0.1";
	//std::cout << "Adresse IP Serveur:";
	//std::cin >> server_ip;
	// std::cout << "Numéro de Port Serveur:";
	// std::cin >> server_port;
	//std::cout << "Adresse IP Client:";
	//std::cin >> client_ip;
	// std::cout << "Numéro de Port Client:";
	// std::cin >> client_port;
	// std::cout << "Entrez votre nom:";
	// std::cin >> name;

	std::cout << server_port << std::endl;
	std::cout << client_port << std::endl;
	std::cout << name << std::endl;

	Game* game = new Game(name,client_port,server_port,client_ip,server_ip);

	(*game).play();
/*
	Client* client = new Client(name,client_port,server_port,client_ip,server_ip);

	std::cout << "synchro_read : " << synchro_read << std::endl;

	while(1){
		usleep(100000);
		std::cout << "synchro_read : " << synchro_read << std::endl;
		std::cout << "Message reçu: " << global_buffer_read << std::endl;
		synchro_read = 0;
	}
	delete client;
	*/
	delete game;
	return 0;
}
