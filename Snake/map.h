#pragma once

#include <SFML\Graphics.hpp>
#include <ctime>
#include <fstream>
#include <string>
#include <iostream>

using namespace sf;
using namespace std;

const int HEIGHT_MAP = 23;
const int WIDTH_MAP = 40;

string TileMap[HEIGHT_MAP];

void read() {
	std::ifstream ifs;
	ifs.open("map.txt");
	string str;

	for (int i = 0; i < HEIGHT_MAP; i++) {
		str = "";
		getline(ifs, str);
		TileMap[i] = str;
	}
}

void foodCreate() {
	srand(time(NULL));
	int a, b;
	for (int i = 0; i < 0; i++) {
		//do {
		a = 1 + (rand() % (HEIGHT_MAP - 3));
		b = 1 + (rand() % (WIDTH_MAP - 2));
		//} while ((TileMap[a][b] == 'o'));
		TileMap[a][b] = 'o';
	}
};

void mapCreate(RenderWindow & window, float S, int WinW, int WinH, int Tx = 32) {
	
	Texture t_map;
	t_map.loadFromFile("images/snake.png");
	Sprite map(t_map);
	map.setScale(S, S);

	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ') map.setTextureRect(IntRect(Tx, Tx, Tx, Tx));
			if (TileMap[i][j] == 's') map.setTextureRect(IntRect(Tx * 2, Tx, Tx, Tx));
			if (TileMap[i][j] == 'o') map.setTextureRect(IntRect(Tx * 3, Tx, Tx, Tx));
			if (TileMap[i][j] == 'h') map.setTextureRect(IntRect(Tx * 3, Tx * 2, Tx, Tx));
			map.setPosition((WinW - WIDTH_MAP * Tx*S) / 2 + j * (32 * S), (WinH - HEIGHT_MAP * Tx*S) / 2 + i * (32 * S));
			window.draw(map);
		}


};