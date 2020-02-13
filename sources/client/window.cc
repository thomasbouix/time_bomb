#include "../../includes/client/window.hh"

Window::Window(std::string name,std::string local_player_name, int length, int width,Color color){
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  window = SDL_CreateWindow(name.c_str(),SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, length, width, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  texts = new Text("font/timeless_bold.ttf",20,color);
  chatbox = new Text("font/timeless_bold.ttf",16,color);
  current_text = new Text("font/timeless_bold.ttf",16,color);
  names = new Text("font/timeless_bold.ttf",20,color);

  (*current_text).add(" ",530,730);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // en blanc
  rect = {0, 0, length, width};
  SDL_RenderFillRect(renderer, &rect);

  Picture* image = new Picture("images/fond.png",1024,768,0,0);
  this->add(image);
  image = new Picture("images/chat.png",485, 490, 525, 265);
  this->add(image);
  image = new Picture("images/red.png",100, 200,30, 500);
  this->add(image);
  claw = new Picture("images/claw.png",75,150,350,290);
  your_turn = false;

  print_values(0,0,0);

  for(int i=0; i<27; i++)
    add_chat(" ",535,275+16*i);

  fill_players(local_player_name);
}

Window::~Window(){
  for( auto& player : players)
    delete player;
  for( auto& picture : pictures)
    delete picture;

  delete texts;
  delete chatbox;
  delete current_text;
  delete names;
  delete claw;

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  TTF_Quit();
  SDL_Quit();

}
std::string Window::get_player_name(int id_player){
  return (*(players[id_player])).get_name();
}
void Window::print_values(int nb_round, int nb_cards_selected, int nb_defusers){
  std::string text;
  (*texts).clear();
  text = "Round played: " + std::to_string(nb_round);
  add_text(text,30,290);
  text = "Cards drew in this round: " + std::to_string(nb_cards_selected);
  add_text(text,30,330);
  text = "Number of defusers found: " + std::to_string(nb_defusers);
  add_text(text,30,370);
}

void Window::add_chat(std::string message, int x, int y){
  (*chatbox).add(message,x,y);
  update();
}

void Window::add_current_text(std::string message){
  (*current_text).replace(message);
  update();
}
void Window::add_text(std::string message,int x,int y){
  (*texts).add(message,x,y);
  update();
}

void Window::add_line(std::string message){
  (*chatbox).add_line(message);
  update();
}


void Window::add(Player* player){
  players.push_back(player);
  update();
}

void Window::add(Picture* picture){
  pictures.push_back(picture);
  update();
}

void Window::fill_players(std::string local_player_name){

/*
F joueur(str) carte1(char) carte2(char)  // distributions de cartes : F thomas S B S D (f = fill) OK
P role(int)								 // role du joueur : P 0 (p = personnage) OK
J nom1(str) nom2(str) // infos sur les joueurs : J 4 aziz thomas theo ludo (j = joueur)
A carte_tiree(char)						 // dévoile la carte qui vient d'être tirée : A S (a = arrivée)
*/
  std::vector<std::string> roles = {"images/blue.png","images/red.png"};
  std::vector<std::string> paths_cards_players = {"images/back.png","images/back.png","images/back.png","images/back.png","images/back.png"};

  std::vector<std::string> paths_cards_localplayer;
  std::string role_localplayer = "";

  std::vector<std::string> name_players;
  int flag_role,flag_card,flag_name;
  bool ready = false;
  while(!ready){           // tant que messages d'initialisations non reçus (F P J)

    if(synchro_read == 1){ // si un message n'a pas été traité par ma boucle graphique
      if(global_buffer_read[0] == 'F'){
        std::string path;
        std::stringstream ss(global_buffer_read);
        while(getline(ss,path,' ')){
          switch ((char)(path[0])){
            case 'S':
              paths_cards_localplayer.push_back("images/safety.png");
            break;
            case 'D':
              paths_cards_localplayer.push_back("images/defuser.png");
            break;
            case 'B':
              paths_cards_localplayer.push_back("images/bomb.png");
            break;
          }
        }
        flag_card = 1;
      }
      if(global_buffer_read[0] == 'P'){
        std::string path;
        std::stringstream ss(global_buffer_read);
        getline(ss,path,' ');
        getline(ss,path,' ');
        role_localplayer = roles[std::stoi(path)];

        flag_role = 1;
      }
      if(global_buffer_read[0] == 'J'){
        std::string path;
        std::stringstream ss(global_buffer_read);
        getline(ss,path,' ');
        while(getline(ss,path,' '))
          name_players.push_back(path);

        flag_name = 1;
      }

      synchro_read = 0;
    }
    if((flag_card == 1) && (flag_role == 1) && (flag_name == 1))
      ready = true;
  }

  local_player = new Player(paths_cards_localplayer,role_localplayer,50,75,1,local_player_name);
  Player* player2 = new Player(paths_cards_players," ",50,75,0,name_players[0]);
  Player* player3 = new Player(paths_cards_players," ",375,75,0,name_players[1]);
  Player* player4 = new Player(paths_cards_players," ",700,75,0,name_players[2]);

  add(player2);
  add(player3);
  add(player4);

  print_names();
}

int Window::find_player_by_name(std::string name){
  for(size_t i = 0; i<players.size(); i++){
    if((*players[i]).get_name() == name)
      return i;
  }
  return -1;
}

void Window::return_card(std::string player_name, int position){
  (*players[find_player_by_name(player_name)]).return_card(position);
  update();
}

void Window::return_card(Player* player, int position){
  (*player).return_card(position);
  update();
}

void Window::remove_card(Player* player, int position){
  (*player).remove_card(position);
  update();
}

void Window::update(){
  SDL_DestroyRenderer(renderer);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_RenderFillRect(renderer, &rect);

  for(const auto& x : pictures)
    (*x).display(renderer);
  for(const auto& x : players)
    (*x).display(renderer);

  if(your_turn == true)
    (*claw).display(renderer);

  if(local_player != NULL)
    (*local_player).display(renderer);

  (*chatbox).display(renderer);
  (*texts).display(renderer);
  (*current_text).display(renderer);
  (*names).display(renderer);

  SDL_RenderPresent(renderer);
}


int select_card_zone(int x, int y, int begin_x,int begin_y,int size){
  for(int i = 0;i < size-1; i++){
    if ( (x>=begin_x+50*i) && (x<begin_x+50*(i+1)) && (y>=begin_y) && (y<begin_y+140) ){
      return i;
    }
  }
  if( (x >= begin_x+50*(size-1)) && (x<begin_x+50*(size-1)+75) && (y>=begin_y) && (y<begin_y+140) )
    return size-1;

  return -1;
}

int select_card_player(int x,int y,int player,int size){
  int card_selected = -1;
  switch(player){
    case 0:
      card_selected = select_card_zone(x,y,50,75,size);
    break;
    case 1:
      card_selected = select_card_zone(x,y,380,75,size);
    break;
    case 2:
      card_selected = select_card_zone(x,y,700,75,size);
    break;
  }
  return card_selected;
}

void Window::select_card(int x,int y,int* player_selected,int* card_selected){
  *player_selected = -1;
  *card_selected = -1;
  for(int i = 0; i<(int)(players.size()); i++){
    *card_selected = select_card_player(x,y,i,players[i]->get_nb_card());
    if(*card_selected != -1){
      *card_selected = *card_selected;
      *player_selected = i;
      return;
    }
  }
}

void Window::set_path(std::string player_name ,int position, std::string card_type){
  (*players[find_player_by_name(player_name)]).set_path(position,card_type);
}

std::string Window::local_player_name(){
  return (*local_player).get_name();
}


void Window::print_names(){
  for(size_t i = 0; i < players.size(); i++)
    (*names).add((*players[i]).get_name(),50+330*i,30);
  (*names).add((*local_player).get_name(),200,700);
  update();
}

void Window::remove_returned_card(){
  for(auto& player : players)
    (*player).remove_returned_card();
}


void Window::set_your_turn(bool your_turn){
  this->your_turn = your_turn;
}
