#pragma once
#include "text.hh"
#include "picture.hh"
#include "color.hh"
#include <SDL.h>
#include <string>
#include "player.hh"
#include "client.hh"

class Window{

  private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect rect;
    std::vector<Picture*> pictures;
    std::vector<Player*> players;
    Player* local_player;
    Text* texts;
    Text* chatbox;
    Text* current_text;
    Text* names;
    Picture* claw;
    bool your_turn;

  public:
    Window(std::string name, std::string local_player_name,int length, int width,Color color);
    ~Window();

    void fill_players(std::string local_player_name);
    void add(Player* player);
    void add(Picture* picture);
    void add_chat(std::string message, int x, int y);
    void add_current_text(std::string message);
    void add_text(std::string message,int x,int y);
    void add_line(std::string message);
    void update();
    void display();
    void return_card(std::string player_name, int position);
    void return_card(Player* player, int position);
    void remove_card(Player* player, int position);
    void select_card(int x,int y,int* player_selected,int* card_selected);
    int find_player_by_name(std::string name);
    void print_values(int nb_round, int nb_cards_selected, int nb_defusers);
    std::string get_player_name(int id_player);
    void set_path(std::string player_name ,int position, std::string card_type);
    std::string local_player_name();
    void print_names();
    void remove_returned_card();
    void set_your_turn(bool your_turn);
};
