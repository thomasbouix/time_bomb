#include "../../includes/client/player.hh"


Player::Player(std::vector<std::string> cards_paths,std::string role_paths, int x, int y, int local_player,std::string name):cards_paths(cards_paths),name(name),x(x),y(y),local_player(local_player){

  if(local_player == 1){
    for(size_t i=0; i<cards_paths.size(); i++){
      Card* card = new Card(cards_paths[i],75,150,200+50*i, 525,local_player);
      cards.push_back(card);
    }
    role = new Card(role_paths,100,200,30,500,local_player);
  }
  else{
    for(size_t i=0; i<cards_paths.size(); i++){
      Card* card = new Card(cards_paths[i],75,150,x+50*i, y,local_player);
      cards.push_back(card);
    }
    role = NULL;
  }
}

Player::~Player(){
  for(auto& card : cards)
    delete card;
  delete role;
}

void Player::remove_card(int position){
  for(auto& card : cards)
    delete card;
  cards.clear();
  cards_paths.erase(cards_paths.begin() + position);
  for(size_t i=0; i<cards_paths.size(); i++){
    Card* card = new Card(cards_paths[i],75,150,x+50*i, y,local_player);
    cards.push_back(card);
  }
}

void Player::return_card(int position){
  (*cards[position]).return_card();
}

void Player::return_card(int position,std::string path){
  set_path(position,path);
  (*cards[position]).return_card();
}

void Player::display(SDL_Renderer* renderer){
  for(auto& card : cards)
    (*card).display(renderer);
  if(local_player == 1)
    (*role).display(renderer);
}

int Player::get_nb_card(){
  return cards_paths.size();
}

std::string Player::get_name(){
  return name;
}

void Player::set_path(int position,std::string card_type){
  if((int)(cards_paths.size()) > position)
    (*cards[position]).set_path(card_type);
}

void Player::remove_returned_card(){
  for(size_t i = 0; i < cards.size(); i++){
    if((*cards[i]).get_status() == 1) // si une carte a été retournée
      this->remove_card(i);
  }
}
