#include <iostream>
#include <sstream>

class Client
{
	private:
		std::string ip;
		int port;
		std::string name;

	public:
		Client(std::string ip, int port, std::string name);
		std::string get_ip();
		int get_port();
		std::string get_name();

};
