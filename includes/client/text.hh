#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "color.hh"
#include <vector>
#include <iostream>

class Text{

  private:
    TTF_Font* font;
    SDL_Color color;
    int size;
    std::vector<std::string> texts;
    std::vector<int> x;
    std::vector<int> y;

  public:
    Text(std::string font_path,int size,Color col);
    ~Text();

    void replace(std::string text);
    void add(std::string text,int x, int y);
    void add_line(std::string message);
    void display(SDL_Renderer* renderer);
    void clear();

};
