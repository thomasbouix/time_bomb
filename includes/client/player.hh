#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include "card.hh"

class Player{

  private:
    std::vector<Card*> cards;
    Card* role;
    std::vector<std::string> cards_paths;
    std::string name;
    int x;
    int y;
    int local_player;


  public:
    Player(std::vector<std::string> cards_paths,std::string role_paths, int x, int y, int local_player,std::string name);
    ~Player();

    void remove_card(int position);
    void return_card(int position);
    void return_card(int position,std::string path);
    void display(SDL_Renderer* renderer);
    int get_nb_card();
    std::string get_name();
    void set_path(int position,std::string card_type);
    void remove_returned_card();
};
