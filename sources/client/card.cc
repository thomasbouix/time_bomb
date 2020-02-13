#include "../../includes/client/card.hh"



Card::Card(std::string path, int length, int width, int x, int y, int status):path(path),length(length),width(width),x(x),y(y),status(status){

  if(status == 1)
    picture = new Picture(path,length,width,x,y);
  else
    picture = new Picture("images/back.png",length,width,x,y);
}

Card::~Card(){
  delete picture;
}

void Card::display(SDL_Renderer* renderer){
  (*picture).display(renderer);
}

void Card::return_card(){
  delete picture;
  status = 1;
  picture = new Picture(path,length,width,x,y);
}

void Card::set_path(std::string card_type){
  switch(card_type[0]){
    case 'D':
      path = "images/defuser.png";
    break;
    case 'S':
      path = "images/safety.png";
    break;
    case 'B':
      path = "images/bomb.png";
    break;
  }
}

int Card::get_status(){
  return status;
}
