#ifndef BUTTON_H
#define BUTTON_H
#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Button {
public:
	Button(String, int, int, int, int, int, int);

	void Draw(RenderWindow &);

	int mouseTrack(RenderWindow &);

	int getWidth();
	int getHeight();

	VideoMode RenWin();

private:
	String File;
	Texture texture;
	Sprite* sprite;
	int sizeX, sizeY;
	int h;
	int n;
	int x, y;
	int menuNum;
};

#endif