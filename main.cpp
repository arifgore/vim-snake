#include <ncurses.h>
#include "player.h"
#include "screen.h"


bool play(Player& snake, WScreen& screen){
	int input = getch();
	bool isOver = false;	
	switch (input) {
		case (int)'h':
			isOver = snake.move('l', screen);
			break;
		case (int)'l':
			isOver = snake.move('r', screen);
			break;
		case (int)'j':
			isOver = snake.move('d', screen);
			break;
		case (int)'k':
			isOver = snake.move('u', screen);
			break;
		case (int)'q':
			return true;
			break;
		default:
			break;
	}
	if(!isOver){
		screen.drawFood();
		screen.drawPlayer(snake.positionsArray, snake.len);
	}	
	return isOver;
}

bool game(){
	WScreen screen = WScreen(40, 120);
	Player player = Player(screen.height, screen.width);
	screen.initColors();
	screen.drawWelcomeScreen();
	getch();
	screen.drawScreen();
	screen.drawBorders();
	screen.drawPlayer(player.positionsArray, player.len);
	screen.drawFood();
	bool isOver = false;
	while(!isOver){
		isOver = play(player, screen);
	}


	while(true){
		int endInput = getch();

		if(endInput == (int)'q'){
			screen.endWindow();
			return true;
		}
		else if (endInput == (int)'r') {
			screen.endWindow();
			return false;
		}
	}	
}

int main(){

	bool isEnd = false;

	while (!isEnd) {
		isEnd = game();
	}
	
	return 0;
}
