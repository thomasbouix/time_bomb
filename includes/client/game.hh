#pragma once
#include "window.hh"
#include "client.hh"
class Game{

  private:
    Window* window;
    Client * client;
    std::string name;
    int nb_round = 0;
    int nb_cards_selected = 0;
    int nb_defusers = 0;

    SDL_Event event;
    int mx,my;
    bool quit;

  public:
    Game(std::string local_player_name, int client_port, int server_port,std::string client_ip, std::string server_ip);
    ~Game();
    void play();

};
