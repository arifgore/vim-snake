#pragma once

#include "position.h"
#include "cstdlib"


class Food{
public:
	Position position;
	

	Food(int height = 40, int width = 120){
		this->newPosition(height, width);
	}

	void newPosition(int height = 40, int width = 120){
		this->position = {rand() % (height - 2) + 1, rand() % (width - 2) + 1};	
	}

};
