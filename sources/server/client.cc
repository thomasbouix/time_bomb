#include "../../includes/client.hh"


Client::Client(std::string ip, int port, std::string name):ip(ip),port(port),name(name){

}

std::string Client::get_ip(){
	return ip;
}

int Client::get_port(){
	return port;
}

std::string Client::get_name(){
	return name;
}
