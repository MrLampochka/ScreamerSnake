#include "Button.h"

Button::Button(String F, int BtX, int BtY, int X, int Y, int H, int N = 1) //download sprites and coords
{
	File = F;
	menuNum = 0;
	texture.loadFromFile("images/" + File);
	Sprite* bt = new Sprite[N];
	for (int i = 0; i < N; i++)
	{
		(bt + i)->setTexture(texture);
		(bt + i)->setTextureRect(IntRect(0, sizeY * i, sizeX, sizeY));
		//(bt + i)->setOrigin(sizeX / 2, sizeY / 2);
		(bt + i)->setPosition(X, Y + i * (sizeY + H));
		sprite = bt;
		n = N;
		h = H;
		x = X; y = Y;
		sizeX = BtX;
		sizeY = BtY;
	}
}

void Button::Draw(RenderWindow & window) //draw buttons
{ 
	mouseTrack(window);
	for (int i = 0; i < n; i++)
		window.draw(*(sprite + i));
};

int Button::mouseTrack(RenderWindow & window) //tracking mouse
{
	for (int i = 0; i < n; i++)
		if (IntRect(x, y + (sizeY + h)*i, sizeX, sizeY).contains(Mouse::getPosition(window))) {
			(sprite + i)->setTextureRect(IntRect(sizeX, sizeY * i, sizeX, sizeY));
			menuNum = i + 1;
			break;
		}
		else {
			(sprite + i)->setTextureRect(IntRect(0, sizeY * i, sizeX, sizeY));
			menuNum = 0;
		}
	return menuNum;

}

int Button::getWidth() { return sizeX; }
int Button::getHeight() { return n * (sizeY + h) - h; }

VideoMode Button::RenWin() //return window settings
{
	VideoMode a(getWidth() + x * 2, getHeight() + y * 2);
	return a;
};