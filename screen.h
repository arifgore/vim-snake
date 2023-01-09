#pragma once

#include <ncurses.h>
#include <string>
#include "position.h"
#include "food.h"

class WScreen{
public:	
	int height, width;
	WINDOW * window;
	Food food;

	WScreen(int height, int width){
		this->height = height;
		this->width = width;
		this->food = Food(40, 120);
		initscr();
		noecho();
		this->window = newwin(height, width, 0, 0);
		refresh();
	}
	
	void initColors(){

		start_color();
		init_pair(1, COLOR_CYAN, COLOR_BLACK);
		init_pair(2, COLOR_RED, COLOR_BLACK);
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);
		init_pair(4, COLOR_BLACK, COLOR_WHITE);
	}



	void drawScreen(){
		
		for(int i = 0; i < this->height; i++){
			for(int j = 0; j < this->width; j++ ){
				mvwaddch(this->window, i, j, ' ' | COLOR_PAIR(1));
			}
		}
		
		wmove(this->window, this->height - 1, this->width - 1);
		wrefresh(this->window);
	}

	void drawBorders(){
		
		for(int col = 0; col < this->width; col++){
			mvwaddch(this->window, 0, col, ' ' | COLOR_PAIR(4));
			mvwaddch(this->window, this->height - 1, col, ' ' | COLOR_PAIR(4));
		}

		for(int row = 0; row < this->width; row++){
			mvwaddch(this->window, row, 0, ' ' | COLOR_PAIR(4));
			mvwaddch(this->window, row, this->width - 1, ' ' | COLOR_PAIR(4));
		}

		wmove(this->window, this->height - 1, this->width - 1);
		wrefresh(this->window);
	}

	void drawFood(){
		
		while(this->getCellContent(this->food.position.row, this->food.position.column) == '+')
			this->food.newPosition(this->height, this->width);

		mvwaddch(
			this->window,
			this->food.position.row,
			this->food.position.column,
			'*' | COLOR_PAIR(3)
		);

		wmove(this->window, this->height - 1, this->width - 1);
		wrefresh(this->window);
	}
	
	void drawPlayer(Position positionsArray[120*40], int len){
		
		mvwaddch(
			this->window,
			positionsArray[0].row,
			positionsArray[0].column,
			'+' | COLOR_PAIR(2)
		);


		for(int i = 1; i < len; i++){
			mvwaddch(
				this->window, 
				positionsArray[i].row, 
				positionsArray[i].column,
				'+' | COLOR_PAIR(1)
			);
		}
		wmove(this->window, this->height - 1, this->width - 1);
		wrefresh(this->window);
	}

	void drawEndScreen(int score){
		std::string scoreStr = std::to_string(score);
		if(scoreStr.length()%2 == 1)
			scoreStr = "0" + scoreStr;

		wattr_on(this->window, COLOR_PAIR(1), NULL);	
		mvwaddstr(this->window, this->height / 2 - 2, this->width / 2 - 2, "GAME");
		mvwaddstr(this->window, this->height / 2 - 1, this->width / 2 - 2, "OVER");
		mvwaddstr(this->window, this->height / 2 + 3, this->width / 2 - 11, "Restart :");
		mvwaddstr(this->window, this->height / 2 + 3, this->width / 2 + 3, "Quit :");
		wattr_off(this->window, COLOR_PAIR(1), NULL);	
		wattr_on(this->window, COLOR_PAIR(2), NULL);	
		mvwaddstr(this->window, this->height / 2, this->width / 2 - 3, "LENGTH");
		mvwaddstr(this->window, this->height / 2 + 1, this->width / 2 - (scoreStr.length()/2), scoreStr.c_str());
		mvwaddstr(this->window, this->height / 2 + 3, this->width / 2 - 2, " r");
		mvwaddstr(this->window, this->height / 2 + 3, this->width / 2 + 9, " q");
		wattr_off(this->window, COLOR_PAIR(2), NULL);	
		wmove(this->window, this->height - 1, this->width - 1);
		wrefresh(this->window);

	}
	
	void drawVictoryScreen(int score){
		std::string scoreStr = std::to_string(score);
		if(scoreStr.length()%2 == 1)
			scoreStr = "0" + scoreStr;
		wattr_on(this->window, COLOR_PAIR(2), NULL);	
		mvwaddstr(this->window, this->height / 2 - 1, this->width / 2 - 4, "YOU WON");
		mvwaddstr(this->window, this->height / 2, this->width / 2 - (scoreStr.length()/2), scoreStr.c_str());
		wattr_off(this->window, COLOR_PAIR(2), NULL);	
		wmove(this->window, this->height - 1, this->width - 1);
		wrefresh(this->window);
	}

	void drawWelcomeScreen(){
		wattr_on(this->window, COLOR_PAIR(2), NULL);	
		mvwaddstr(this->window, this->height / 2 - 3, this->width / 2 - 7, "MOVE LEFT  :");
		mvwaddstr(this->window, this->height / 2 - 2, this->width / 2 - 7, "MOVE RIGHT :");
		mvwaddstr(this->window, this->height / 2 - 1, this->width / 2 - 7, "MOVE UP    :");
		mvwaddstr(this->window, this->height / 2 , this->width / 2 - 7, "MOVE DOWN  :");
		mvwaddstr(this->window, this->height / 2 + 2 , this->width / 2 - 25, "If multiple choices nerve you, just press enter...");
		wattr_off(this->window, COLOR_PAIR(2), NULL);	
		wattr_on(this->window, COLOR_PAIR(1), NULL);	
		mvwaddstr(this->window, this->height / 2 - 3, this->width / 2 + 5, " h");
		mvwaddstr(this->window, this->height / 2 - 2, this->width / 2 + 5, " l");
		mvwaddstr(this->window, this->height / 2 - 1, this->width / 2 + 5, " k");
		mvwaddstr(this->window, this->height / 2 , this->width / 2 + 5, " j");
		mvwaddstr(this->window, this->height / 2 + 1 , this->width / 2 - 11, "Press any key to start");
		wattr_off(this->window, COLOR_PAIR(1), NULL);	
		wmove(this->window, this->height - 1, this->width - 1);
		wrefresh(this->window);
	}

	char getCellContent(int cellRow, int cellColumn){
		chtype* chstr = new chtype[1];
		wmove(this->window, cellRow, cellColumn);
		winchnstr(this->window, chstr, 1);
		char character = chstr[0] & A_CHARTEXT;
		return(character);
	}

	void deleteChar(int row, int column){
		mvwaddch(this->window, row, column, ' ');
		wmove(this->window, this->height - 1, this->width -1 );
		wrefresh(this->window);
	}

	void endWindow(){
		endwin();
	}
};
