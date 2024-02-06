#include <iostream>
#include <conio2.h>

const int WIDTH = 70;
const int HEIGHT = 16;
const char WALL_CHAR = '#';
const char ENEMY_CHAR = '|';
const char PLAYER_CHAR = '@';
const int COUNT_DOWN = 1000000000; 
int score = 0; 
int countDown = COUNT_DOWN;




void drawStats() { 
	gotoxy(1, HEIGHT + 5);
	std::cout << "Countdown: " << countDown;
	std::cout << "    Use 'W', 'A', 'S', 'D' to move the '@'.";
	std::cout << "    Score: " << score;
	--countDown;
}

void drawScene(int playerX, int playerY) {
	
	clrscr();
	
	std::cout << " ";
	for (int i = 0; i < WIDTH - 2; ++i)
		std::cout << WALL_CHAR;
	std::cout << " \n";
	
	
	for (int i = 0; i < HEIGHT - 3; ++i) {
		std::cout << WALL_CHAR;
		for (int j = 0; j < WIDTH - 4 ; ++j) { 
				std::cout << " ";
		}
		std::cout << WALL_CHAR;
		std::cout << " \n";
	}
	
	
	std::cout << WALL_CHAR;
	for (int i = 0; i < WIDTH - 2; ++i)
		std::cout << WALL_CHAR;
	std::cout << " \n";
	
	
	gotoxy(playerX, playerY);
	std::cout << PLAYER_CHAR;
	
	gotoxy(WIDTH / 2, HEIGHT / 2);
	std::cout << ENEMY_CHAR << "###" <<ENEMY_CHAR;
	
	drawStats();
	
}

int main() {
	int playerX = WIDTH / 2, playerY = HEIGHT - 3;
	drawScene(playerX, playerY);
	
	while (countDown > 0) {		
		if (_kbhit()) {
			char key = _getch();
			switch (key) {
			case 'w':
			case 'W':
				if (playerY > 2)
					playerY--;
				else{
					score++;
					playerX = WIDTH / 2; 
					playerY = HEIGHT - 3;
					drawScene(playerX, playerY);
				}
				break;
			case 'a':
			case 'A':
				if (playerX > 2)
					playerX--;
				break;
			case 's':
			case 'S':
				if (playerY < HEIGHT - 2)
					playerY++;
				break;
			case 'd':
			case 'D':
				if (playerX < WIDTH - 3)
					playerX++;
				break;
			}
			drawScene(playerX, playerY);
		}
		drawStats();
	}
	
	return 0;
}

