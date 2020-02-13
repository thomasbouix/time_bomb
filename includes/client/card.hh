#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include "picture.hh"


class Card{

  private:
    Picture* picture;
    std::string path;
    int length;
    int width;
    int x;
    int y;
    int status;


  public:
    Card(std::string path, int length, int width, int x, int y, int status);
    ~Card();

    void display(SDL_Renderer* renderer);
    void return_card();
    void set_path(std::string card_type);
    int get_status();
};
