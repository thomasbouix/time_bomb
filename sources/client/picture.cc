#include "../../includes/client/picture.hh"

Picture::Picture(std::string path, int length, int width, int x, int y):length(length),width(width),x(x),y(y){
  surface = IMG_Load(path.c_str());
  rect = { x, y, length, width };
}

Picture::~Picture(){
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

void Picture::change_position(int x,int y){
  rect = { x, y, length, width };
}

void Picture::display(SDL_Renderer* renderer){
  texture = SDL_CreateTextureFromSurface(renderer,surface);
  SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
