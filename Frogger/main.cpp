#include <iostream>
#include <conio2.h>
#include <windows.h>
#include <utility> 
#include <vector>


class GameObject{
public:
	virtual void update(const std::pair<int, int>& window) = 0;
	virtual void draw(const std::pair<int, int>& window) = 0;
};

class Player : public GameObject{
private:
	const char PLAYER_CHAR = '@';
	const int INITX;
	const int INITY;
	std::pair<int, int> pos = std::make_pair(INITX, INITY);
	
public:	
	Player(int x, int y) :  INITX(x), INITY(y){}	
	void update(const std::pair<int, int>& window) override;
	void draw(const std::pair<int, int>& window) override{
		textcolor(GREEN);
		gotoxy(pos.first, pos.second);
		std::cout << PLAYER_CHAR;
		textcolor(WHITE);
	}
	std::pair<int, int> getPos(){ return pos; }
	void resetPos() {
		pos.first = INITX; 
		pos.second = INITY;
	}
	
	bool flag = false;
};

void Player::update(const std::pair<int, int>& window){
	if (_kbhit()) {
		char key = _getch();
		switch (key) {
		case 'w':
		case 'W':
			if (pos.second > 2)
				pos.second--;
			else{
				flag = true;
				resetPos();
			}
			break;
		case 'a':
		case 'A':
			if (pos.first > 2)
				pos.first--;
			break;
		case 's':
		case 'S':
			if (pos.second < window.second - 2)
				pos.second++;
			break;
		case 'd':
		case 'D':
			if (pos.first < window.first - 3)
				pos.first++;
			break;
		}
	}
}
class Enemy: public GameObject{
private:
	const char ENEMY_CHAR = '|';
	const int INITX;
	const int INITY;
	std::pair<int, int> pos = std::make_pair(INITX, INITY);
public:
	Enemy(int x, int y) :  INITX(x), INITY(y){}
	void update(const std::pair<int, int>& window) override{}
	void draw(const std::pair<int, int>& window) override{
		textcolor(RED);
		textbackground(RED);
		gotoxy(pos.first, pos.second);
		std::cout << ENEMY_CHAR << ENEMY_CHAR <<ENEMY_CHAR;
		
		if(pos.first > window.first - 4)
			pos.first = INITX;
		else
			pos.first+=1;
		
		textcolor(WHITE);
		textbackground(BLACK);
	}
	
	std::pair<int, int> getPos(){ return pos; }
};

class Juego{
private:
	const int WIDTH = 70;
	const int HEIGHT = 20;
	const std::pair<int, int> window = std::make_pair(WIDTH, HEIGHT);
	std::vector<Enemy> enemies;
	Player player;
	const char WALL_CHAR = '#';
	const int COUNT_DOWN = 1000000000; 
	int countDown = COUNT_DOWN;
	int score = 0; 
	void collision();
	void update();
	void draw();
public:
	Juego();
	void run();
};

Juego::Juego() : player((int)(window.first / 2), (int)(window.second - 3)){
	enemies.push_back(Enemy(4, 5));
	enemies.push_back(Enemy(14, 5));
	enemies.push_back(Enemy(24, 5));
	enemies.push_back(Enemy(4, 10));
	enemies.push_back(Enemy(14, 10));
	enemies.push_back(Enemy(24, 10));
}

void Juego::collision() {	
	for(Enemy enemy : enemies){
		if(player.getPos().first == enemy.getPos().first && player.getPos().second == enemy.getPos().second ||
		   player.getPos().first == enemy.getPos().first + 1 && player.getPos().second == enemy.getPos().second ||
		   player.getPos().first == enemy.getPos().first + 2 && player.getPos().second == enemy.getPos().second){
			score--;
			player.resetPos();
		}
	}		
}

void Juego::run(){
	while (countDown > 0 && score >= 0){
		clrscr();
		update();
		draw();
		Sleep(100);
	}
}

void Juego::update(){
	collision();
	--countDown;
	player.update(window);
	if(player.flag){
		score++;
		player.flag = false;
	}
	
}

void Juego::draw(){
	
	textcolor(LIGHTBLUE);
	textbackground(LIGHTBLUE);
	std::cout << " ";
	for (int i = 0; i < window.first - 4; ++i)
		std::cout << WALL_CHAR;
	std::cout << " \n";
	
	
	for (int i = 0; i < window.second - 3; ++i) {
		textcolor(LIGHTBLUE);
		textbackground(LIGHTBLUE);
		std::cout << WALL_CHAR;
		for (int j = 0; j < WIDTH - 4 ; ++j) { 
			textcolor(WHITE);
			textbackground(BLACK);
			std::cout << " ";
		}
		textcolor(LIGHTBLUE);
		textbackground(LIGHTBLUE);
		std::cout << WALL_CHAR;
		std::cout << " \n";
	}
	
	
	std::cout << WALL_CHAR;
	for (int i = 0; i < window.first - 3; ++i)
		std::cout << WALL_CHAR;
	std::cout << " \n";
	
	textcolor(WHITE);
	textbackground(BLACK);
	gotoxy(1, window.second + 2);
	std::cout << "Countdown: " << countDown;
	std::cout << "    Use 'W', 'A', 'S', 'D' to move";
	std::cout << "    Score: " << score;
	
	player.draw(window);
	for(Enemy& enemy : enemies)
		enemy.draw(window);
}


int main() {
	Juego j;
	j.run();
	return 0;
}


