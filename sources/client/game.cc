#include "../../includes/client/game.hh"


Game::Game(std::string local_player_name, int client_port, int server_port,std::string client_ip, std::string server_ip){
  Color color(174,100,56);
  name = local_player_name;
  std::cout << "Client" << std::endl;
	client = new Client(local_player_name,client_port,server_port,client_ip,server_ip);
  std::cout << "Window" << std::endl;
	window = new Window("TimeBomb",local_player_name,1024,768,color);

}


Game::~Game(){
  delete client;
  delete window;
}



#define ENTER 13
#define EFFAC 8

void Game::play(){

  std::string message = name + ": ";
  quit = false;
  int player_selected = 0;
  int card_selected = 0;
  while(!quit){
    if (SDL_PollEvent(&event)){
      switch (event.type){
        case SDL_QUIT:
          quit = true;

        break;
			  case  SDL_MOUSEBUTTONDOWN:
          SDL_GetMouseState( &mx, &my );
          (*window).select_card(mx,my,&player_selected,&card_selected);
          if((player_selected != -1) && (card_selected != -1)){
            std::stringstream ss;
            ss << "draw " << (*window).get_player_name(player_selected) << " " << card_selected;
            global_buffer_write = ss.str();
            synchro_write = 1;
            while(synchro_write);
          }

          std::cout << "X: " << mx << "-- Y: " << my << std::endl;

        break;
        case  SDL_MOUSEMOTION:
          SDL_GetMouseState( &mx, &my );
        break;

        case SDL_TEXTINPUT:
          if(message.size() < 40){
            message = message + event.text.text;
            (*window).add_current_text(message);
          }
          break;
        case SDL_KEYUP:
          auto key = event.key.keysym.sym;
          if(key == ENTER){
            global_buffer_write = message;
            synchro_write = 1;
            while(synchro_write);

            (*window).add_line(message);
            message = name + ": ";
            (*window).add_current_text(message);
          }
          else if(key == EFFAC){
            if(message.size() != name.size()+1)
              message = message.substr(0,message.size()-1);
            else
              message = name + ": ";
            (*window).add_current_text(message);
          }

          break;
      }
    }
    // Gestion reception valeurs
    /*
    R nb_rd(int) // round actuel (r = round)
    C nb_c(int)  // nombres de cartes tirées dans le round(c = carte)
    D nb_d(int)  // defusers trouvés dans la partie (d = defuser)
    */
    /*if(synchro_read == 1){ // message en attente de traitement par la boucle graphique
      (*window).add_line(global_buffer_read);
      synchro_read = 0;
    }
    */
    if(synchro_read == 1){
      std::stringstream ss(global_buffer_read);
      std::string path;
      if(global_buffer_read[0] == 'R'){
        getline(ss,path,' ');
        getline(ss,path,' ');
        nb_round = std::atoi(path.c_str());
        (*window).print_values(nb_round, nb_cards_selected, nb_defusers);
        (*window).remove_returned_card();
      }
      if(global_buffer_read[0] == 'C'){
        getline(ss,path,' ');
        getline(ss,path,' ');
        nb_cards_selected = std::atoi(path.c_str());
        (*window).print_values(nb_round, nb_cards_selected, nb_defusers);
      }
      if(global_buffer_read[0] == 'D'){
        getline(ss,path,' ');
        getline(ss,path,' ');
        nb_defusers = std::atoi(path.c_str());
        (*window).print_values(nb_round, nb_cards_selected, nb_defusers);
      }
      if(global_buffer_read[0] == 'A'){
        std::vector<std::string> draw_data;
        getline(ss,path,' ');
        while(getline(ss,path,' '))
          draw_data.push_back(path);

        if(draw_data[0] == (*window).local_player_name())
          (*window).set_your_turn(true);
        else
          (*window).set_your_turn(false);

        if(draw_data[0] != (*window).local_player_name()){
          (*window).set_path(draw_data[0] ,std::atoi(draw_data[1].c_str()), draw_data[2]);
          (*window).return_card(draw_data[0],std::atoi(draw_data[1].c_str()));
        }
      }
      //if(global_buffer_read[1] == ' ')
      //  global_buffer_read = "";

      (*window).add_line(global_buffer_read);
      synchro_read = 0;
    }


  }
}
