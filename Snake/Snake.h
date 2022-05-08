//#ifndef SNAKE_H
//#define SNAKE_H
//#pragma once
//
//#include <SFML/Audio.hpp>
//#include "map.h"
//using namespace sf;
//
//class Snake {
//private:
//
//	float tx, timer = 0, size, k;
//	int dir;
//	bool speed;
//	int spv = 10;
//	String File;
//	Texture texture;
//	Sprite spHead, spBody, spBody90, spTail;
//	int score = 0;
//	struct Body { int x, y; }  s[1000];
//	int num;
//	int difW, difH;
//	int life = 3;
//	SoundBuffer h, b, m;
//	Sound heart, bell, money;
//
//public:
//
//	Snake(int, int, String, int, float, int, int, int, int );
//
//
//	int getCoordX(int);
//	int getCoordY(int);
//	int getLife();
//	int getScore();
//	int getNum();
//	int getTimer();
//	Sprite getSprite();
//	int getSpriteRotation();
//
//
//	float spd(float);
//
//	void setDirection(int);
//
//	void Turbo();
//
//	void update(Snake&, float, float&);
//
//	void deadSnake(int, int, float&);
//
//	void interSnake(Snake&, float&);
//
//	void interMap(int, float&);
//
//	void Draw(RenderWindow & );
//};
//
//#endif