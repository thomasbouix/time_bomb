#pragma once
#include "player.hh"

class Real : public Player {

	public :
		Real();
		Real(int color, std::string name);
		virtual void draw();
		virtual void draw(Player* p, int card);
};
