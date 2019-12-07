#pragma once
#include "bot.hh"

class Weak : public Bot {

	public :
		Weak();
		Weak(int c);
		virtual void draw();
		using Player::draw;
};