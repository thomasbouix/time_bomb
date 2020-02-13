#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

class Picture{

  private:
    SDL_Surface *surface;
    SDL_Texture * texture;
    SDL_Rect rect;
    int length,width,x,y;

  public:
    Picture(std::string path, int length, int width, int x, int y);
    ~Picture();

    void change_position(int x,int y);
    void display(SDL_Renderer* renderer);
};
