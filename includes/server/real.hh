#pragma once
#include "player.hh"

class Real : public Player {

	public :
		Real();
		Real(int color, std::string name);
		virtual void draw();

		using Player::draw;
		/*	
		 *	obligé sinon -> error: no matching function for call to ‘Real::draw(Player*, int)’
		 * 	En effet, Real::draw() masque Player::draw(Player*, int) dans la classe mère
		 *	On indique donc au compilateur qu'on utilise des fonctions définies plus haut dans la hiérarchie
		 */
};
