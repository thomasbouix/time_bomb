#pragma once
#include <iostream>
#include <string>

class Card {

	public :
		virtual ~Card();
		virtual std::string to_string() const = 0;

};