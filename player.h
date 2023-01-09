#pragma once

#include "food.h"
#include "position.h"
#include "screen.h"

class Player{
public:
	Position positionsArray[118*38];
	Position headPosition;
	int len;
	char direction;

	Player(int height, int width){
		this->headPosition = {rand() % (height - 2) + 1, rand() % (width - 2) + 1};
		this->positionsArray[0] = headPosition;
		this->len = 1; 
		this->direction = 'n';
	}

	void eat(Food& food){
		this->len++;
		food.newPosition(40, 120);
	}

	Position getNewHeadPosition(char direction){
		switch (direction) {
			case 'l':
				if(this->direction != 'r'){
					this->direction = 'l';
					return((Position){this->headPosition.row,
							--this->headPosition.column});
				}
				break;
			case 'r':
				if(this->direction != 'l'){
					this->direction = 'r';
					return((Position){this->headPosition.row,
							++this->headPosition.column});
				}
				break;
			case 'u':
				if(this->direction != 'd'){
					this->direction = 'u';
					return((Position){--this->headPosition.row,
							this->headPosition.column});
				}
				break;
			case 'd':
				if(this->direction != 'u'){
					this->direction = 'd';
					return((Position){++this->headPosition.row,
							this->headPosition.column});
				}
				break;
			default:
				return(this->headPosition);
		}
		return(this->headPosition);
	}

	bool move(char direction, WScreen& myscreen){
		Position oldPosition = this->positionsArray[this->len - 1];
		Position newHeadPosition = this->getNewHeadPosition(direction);
		if(newHeadPosition.row == this->positionsArray[0].row && newHeadPosition.column == this->positionsArray[0].column)
			return false;

		if(newHeadPosition.row >= myscreen.height -1	||
		   newHeadPosition.row <= 0			||
		   newHeadPosition.column >= myscreen.width -1	||
		   newHeadPosition.column <= 0
		){
			myscreen.drawEndScreen(this->len);	
			return true; 
		}


		char character = myscreen.getCellContent(newHeadPosition.row, newHeadPosition.column);


		if(character == '+'){
			if(newHeadPosition.row != this->positionsArray[this->len - 1].row ||
			   newHeadPosition.column != this->positionsArray[this->len - 1].column
			){
				myscreen.drawEndScreen(this->len);	
				return true; 
			}
		}

		myscreen.deleteChar(oldPosition.row, oldPosition.column);
		

		if(newHeadPosition.row == myscreen.food.position.row && newHeadPosition.column == myscreen.food.position.column){
			this->eat(myscreen.food);
			if(this->len == myscreen.height * myscreen.width - 5){
				myscreen.drawVictoryScreen(this->len);
				return true;
			}
		}

		for(int i = len - 2; i >= 0; i--){
			this->positionsArray[i+1] = this->positionsArray[i];
		}
		this->positionsArray[0] = newHeadPosition;
		return false;	
	}
};

