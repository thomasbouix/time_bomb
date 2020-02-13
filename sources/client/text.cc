#include "../../includes/client/text.hh"


Text::Text(std::string font_path,int size,Color col){
  font = TTF_OpenFont(font_path.c_str(),size);
  color = {col.R,col.G,col.B};
}

Text::~Text(){
  TTF_CloseFont(font);
}

void Text::clear(){
  texts.clear();
}
void Text::replace(std::string text){
  this->texts.clear();
  this->texts.push_back(text);
}
void Text::add(std::string text,int x, int y){
  this->texts.push_back(text);
  this->x.push_back(x);
  this->y.push_back(y);
}

void Text::display(SDL_Renderer* renderer){
  for(size_t i=0; i<texts.size(); i++){
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect rect;

    surface = TTF_RenderText_Solid(font,texts[i].c_str(), color);
    rect.x = x[i];
    rect.y = y[i];
    rect.w = surface->w;
    rect.h = surface->h;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

  }

}

void Text::add_line(std::string message){
  this->texts.erase(this->texts.begin());
  this->texts.push_back(message);
}
