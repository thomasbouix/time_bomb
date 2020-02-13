#pragma once
#include "bot.hh"

class Strong : public Bot {

	public :
		Strong();
		Strong(int c);
		virtual void draw();
		using Player::draw;
};