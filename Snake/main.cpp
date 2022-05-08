#include <sstream>
#include "Menu.h"
#include "Snake.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"

class Snake {
private:
	
	float tx, timer = 0, size, k;
	int dir;
	bool speed = false;
	int spv = 10;
	String File;
	Texture texture;
	Sprite spHead, spBody, spBody90, spTail;
	int score = 0;
	struct Body { int x, y; }  s[1000];
	int num;
	int difW, difH;
	int life = 3;
	SoundBuffer h, b, m;
	Sound heart, bell, money;
public:

	Snake(int WinW, int WinH, String F, int Tx = 32, float S = 1, int X = 1, int Y = 1, int D = 1, int N = 1)
	{
		File = F;
		tx = Tx;
		dir = D; size = S;
		num = N;
		k = size * tx;
		difW = (WinW - WIDTH_MAP * k) / 2;
		difH = (WinH - HEIGHT_MAP * k) / 2;
		s[0].x = difW + k / 2 + X * k;
		s[0].y = difH + k / 2 + Y * k;

		texture.loadFromFile("images/" + File);

		spHead.setTexture(texture); spHead.setTextureRect(IntRect(0, 32, tx, tx)); spHead.setOrigin(tx / 2, tx / 2); spHead.setScale(size, size);
		spBody.setTexture(texture); spBody.setTextureRect(IntRect(64, 0, tx, tx)); spBody.setOrigin(tx / 2, tx / 2); spBody.setScale(size, size);
		spBody90.setTexture(texture); spBody90.setTextureRect(IntRect(96, 0, tx, tx)); spBody90.setOrigin(tx / 2, tx / 2); spBody90.setScale(size, size);
		spTail.setTexture(texture); spTail.setTextureRect(IntRect(32, 0, tx, tx)); spTail.setOrigin(tx / 2, tx / 2); spTail.setScale(size, size);

		spHead.setRotation(90 * D);
		spHead.setPosition(s[0].x, s[0].y);

		h.loadFromFile("music/heart.ogg");//загружаем в него звук
		heart.setBuffer(h);//создаем звук и загружаем в него звук из буфера

		b.loadFromFile("music/bell.ogg");
		bell.setBuffer(b);//создаем звук и загружаем в него звук из буфера

		m.loadFromFile("music/money.ogg");
		money.setBuffer(m);//создаем звук и загружаем в него звук из буфера
	};

	int getCoordX(int n) { return s[n].x; };
	int getCoordY(int n) { return s[n].y; };
	int getLife() { return life; };
	int getScore() { return score; }
	int getNum() { return num; };
	int getTimer() { return timer; };
	Sprite getSprite() { return spHead; }
	int getSpriteRotation() { return spHead.getRotation(); }


	float spd(float gameTime) {
		if ((speed == true) && (score>0) && (spv>0)) {
			return gameTime / 2;
		}
		else {
			speed = false;
			spv = 10;
			return gameTime;
		}
	};

	void setDirection(int D) { dir = D; }

	void Turbo() { speed = true; }

	void update(Snake& sn, float time, float& gameTime)
	{
		timer += time;
		if (timer > spd(gameTime)) {
			
			timer -= spd(gameTime);

			if (speed == true)
			{
				score--; spv--;
				if (spv==0 || score==0)
					timer = sn.getTimer();
			}

			for (int i = num; i > 0; --i)
			{
				s[i].x = s[i - 1].x; s[i].y = s[i - 1].y;
			}

			switch (dir)
			{
			case 0: s[0].y -= k; spHead.setRotation(0);  break;
			case 1: s[0].x += k; spHead.setRotation(90); break;
			case 2: s[0].y += k; spHead.setRotation(180); break;
			case 3: s[0].x -= k; spHead.setRotation(270); break;
			}

			interSnake(sn, gameTime);
			interMap(dir, gameTime);
		}
	};

	void deadSnake(int a, int b, float& gameTime) {
		
		for (int i = b; i<a+num; i++) {
			
			int m = (s[i].y - difH - k / 2) / k;
			int t = (s[i].x - difW - k / 2) / k;

			if (TileMap[m][t] != 'o')
			TileMap[m][t] = 'o';

			s[i].x = -32; s[i].y = -32;
		};
		
		num = 1;

		do {
			a = 1 + (rand() % (HEIGHT_MAP - 3));
			b = 1 + (rand() % (WIDTH_MAP - 2));
		} while ((TileMap[a][b] == 'o') || (TileMap[a][b] == 's') || (TileMap[a][b] == 'h'));


		s[0].x = b * k + k / 2 + difW;
		s[0].y = a * k + k / 2 + difH;
		gameTime = 1000;
		score = 0;
		life--;
		bell.play();
	};

	void interSnake(Snake& sn, float& gameTime) {
		if ((s[0].x == sn.getCoordX(0)) && (s[0].y == sn.getCoordY(0))) {
			if (num==sn.getNum())
			{sn.deadSnake(0,0, gameTime); deadSnake(1,1, gameTime);}
			else {
				if (num < sn.getNum()) 
				{deadSnake(1,1, gameTime);}
				else {sn.deadSnake(0,0, gameTime);}
			}
			return;
		}

		for (int g = 1; g < sn.getNum(); g++)
			if ((s[0].x == sn.getCoordX(g)) && (s[0].y == sn.getCoordY(g))) {
				deadSnake(1,1, gameTime);
				return;
			}
		
		for (int g = 1; g < num; g++)
			if ((s[0].x == s[g].x) && (s[0].y == s[g].y)) {
				deadSnake(0,1, gameTime);
				return;
			}
	}

	void interMap(int D, float& gameTime) {
		int i = (s[0].y - difH - k / 2) / k;
		int j = (s[0].x - difW - k / 2) / k;
		{
			if (TileMap[i][j] == 's') {
				deadSnake(1,1, gameTime);
				return;
			}

			if (TileMap[i][j] == 'o') {
				TileMap[i][j] = ' ';

				do {
					i = 1 + (rand() % (HEIGHT_MAP - 3));
					j = 1 + (rand() % (WIDTH_MAP - 2));
				} while ((TileMap[i][j] == 'o') || (TileMap[i][j] == 's')|| (TileMap[i][j] == 'h'));
				
				TileMap[i][j] = 'o';

				if (rand() % 30 == 1) {
					do {
						i = 1 + (rand() % (HEIGHT_MAP - 3));
						j = 1 + (rand() % (WIDTH_MAP - 2));
					} while ((TileMap[i][j] == 'o') || (TileMap[i][j] == 's') || (TileMap[i][j] == 'h'));
					TileMap[i][j] = 'h';
				}
					score++;
					num++;
					money.play();
					return;
			}

			if (TileMap[i][j] == 'h') {
				TileMap[i][j] = ' ';
				life++;
				score+=5;
				heart.play();
				return;
			}

		}
	};

	void Draw(RenderWindow & window) {
		spHead.setTextureRect(IntRect(0, 32, tx, tx));
		if (num > 1) {
			spHead.setTextureRect(IntRect(0, 0, tx, tx));
			for (int i = 1; i < num; i++) {
				if (i == num - 1) {
					if (s[i - 1].x > s[i].x)
						spTail.setRotation(270);
					if (s[i - 1].x < s[i].x)
						spTail.setRotation(90);
					if (s[i - 1].y > s[i].y)
						spTail.setRotation(0);
					if (s[i - 1].y < s[i].y)
						spTail.setRotation(180);
					spTail.setPosition(s[i].x, s[i].y);
					window.draw(spTail);
				}
				else {
					if ((s[i - 1].x != s[i + 1].x) && (s[i - 1].y != s[i + 1].y)) {
						if (s[i - 1].x > s[i].x)
							if (s[i].y > s[i + 1].y)
								spBody90.setRotation(270);
							else
								spBody90.setRotation(0);
						if (s[i - 1].x < s[i].x)
							if (s[i].y > s[i + 1].y)
								spBody90.setRotation(180);
							else
								spBody90.setRotation(90);
						if (s[i - 1].y > s[i].y)
							if (s[i].x > s[i + 1].x)
								spBody90.setRotation(90);
							else
								spBody90.setRotation(0);
						if (s[i - 1].y < s[i].y)
							if (s[i].x > s[i + 1].x)
								spBody90.setRotation(180);
							else
								spBody90.setRotation(270);

						spBody90.setPosition(s[i].x, s[i].y);
						window.draw(spBody90);
					}
					else {
						if (s[i - 1].x != s[i].x)
							spBody.setRotation(90);
						if (s[i - 1].y != s[i].y)
							spBody.setRotation(0);
						spBody.setPosition(s[i].x, s[i].y);
						window.draw(spBody);
					}
				}
				
			}
		}
		spHead.setPosition(s[0].x,s[0].y);
		window.draw(spHead);
	};

};

int main()
{
	
		Music mus;//создаем объект музыки
		mus.openFromFile("music/mus.ogg");//загружаем файл
		mus.setLoop(true);

begin:	mus.play();//воспроизводим музыку
		read();
		if (menu() == false)
			exit(0); else {
  
			srand(time(NULL));

			VideoMode as = VideoMode::getDesktopMode();
			bool pause = false;
			int WinH = 1080;
			int WinW = 1920;
			float Size = 1.5;
			int Tx = 32;
			float gameTime = 1000, timer = 0;
			float gameTime1 = gameTime, gameTime2 = gameTime;
			Font font;
			font.loadFromFile("fonts/font.ttf");
			Text text("", font, 20);

			Clock clock;

			foodCreate();

			RenderWindow window(as, "Snake", Style::Fullscreen);
			Image icon;
			icon.loadFromFile("images/icon.png");
			window.setIcon(32, 32, icon.getPixelsPtr());

			window.setFramerateLimit(30);
			window.setVerticalSyncEnabled(true);

			Snake s1(WinW, WinH, "snake.png", 32, Size, 3, 3, 2, 1);
			Snake s2(WinW, WinH, "snake2.png", 32, Size, 36, 18, 0, 1);

			SoundBuffer screamBuffer;//создаём буфер для звука

			screamBuffer.loadFromFile("music/scream.ogg");
			Sound scream(screamBuffer);//создаем звук и загружаем в него звук из буфера

			Texture scrT;
			scrT.loadFromFile("images/notscreamer.png");
			Sprite scr(scrT);
			scr.setScale(3, 3);
			scr.setPosition(430, 250);

			while (window.isOpen())
			{
				std::ostringstream playerscore1;
				std::ostringstream playerscore2;
				std::ostringstream playerlife1;
				std::ostringstream playerlife2;


				float time = clock.getElapsedTime().asMicroseconds();
				clock.restart();
				time = time / 1000;

				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
				}

				{//Клавиши

					if (Keyboard::isKeyPressed(Keyboard::Escape)) { window.close(); };

					if ((Keyboard::isKeyPressed(Keyboard::A)) && (s1.getSpriteRotation() != 90))s1.setDirection(3);
					if ((Keyboard::isKeyPressed(Keyboard::D)) && (s1.getSpriteRotation() != 270))s1.setDirection(1);
					if ((Keyboard::isKeyPressed(Keyboard::W)) && (s1.getSpriteRotation() != 180))s1.setDirection(0);
					if ((Keyboard::isKeyPressed(Keyboard::S)) && (s1.getSpriteRotation() != 0)) s1.setDirection(2);
					if (Keyboard::isKeyPressed(Keyboard::LShift)) { s1.Turbo(); }

					if (Keyboard::isKeyPressed(Keyboard::Left) && (s2.getSpriteRotation() != 90))s2.setDirection(3);
					if (Keyboard::isKeyPressed(Keyboard::Right) && (s2.getSpriteRotation() != 270))s2.setDirection(1);
					if (Keyboard::isKeyPressed(Keyboard::Up) && (s2.getSpriteRotation() != 180))s2.setDirection(0);
					if (Keyboard::isKeyPressed(Keyboard::Down) && (s2.getSpriteRotation() != 0)) s2.setDirection(2);
					if (Keyboard::isKeyPressed(Keyboard::RShift)) { s2.Turbo(); };

					if (Keyboard::isKeyPressed(Keyboard::Space)) { if (pause == false) pause = true; else pause = false; };
					if (pause == true) time = 0;

				}

				window.clear(Color::Color(0, 84, 11, 255));

				mapCreate(window, Size, WinW, WinH, Tx);

				text.setCharacterSize(40);

				text.setFillColor(Color::Red);
				text.setPosition((WinW - WIDTH_MAP * Tx*Size) / 2 + 1 * (Tx * Size), (WinH - HEIGHT_MAP * Tx*Size) / 2 + 21 * (32 * Size));
				playerscore1 << s1.getScore();
				playerlife1 << s1.getLife();
				text.setString("Player 1 | Score: " + playerscore1.str() + " | Life: " + playerlife1.str());
				window.draw(text);


				text.setFillColor(Color::Blue);
				text.setPosition((WinW - WIDTH_MAP * Tx*Size) / 2 + 20 * (Tx * Size), (WinH - HEIGHT_MAP * Tx*Size) / 2 + 21 * (32 * Size));
				playerscore2 << s2.getScore();
				playerlife2 << s2.getLife();
				text.setString("Player 2 | Score: " + playerscore2.str() + " | Life: " + playerlife2.str());
				window.draw(text);

				text.setFillColor(Color::White);

				s1.update(s2, time, gameTime1);
				s2.update(s1, time, gameTime2);

				if (gameTime1 == 1000 || gameTime2 == 1000)
					gameTime = 1000;
				timer += time;
				if (timer > 1000) { timer = 0; if (gameTime > 100) gameTime -= 10; }
				gameTime1 = gameTime;
				gameTime2 = gameTime;


				if (s1.getLife() == 0 || s2.getLife() == 0) {

					text.setPosition(500, 150);
					scream.play();
					mus.stop();

					if (s1.getLife() == 0)
						text.setString("Player 2 win!   Score: " + playerscore2.str() + "             (press Esc)");
					else
						text.setString("Player 1 win!   Score: " + playerscore1.str() + "             (press Esc)");

					while (!Keyboard::isKeyPressed(Keyboard::Escape)) {

						window.clear();
						window.draw(scr);
						window.draw(text);
						window.display();
					}
					goto begin;
				}

				s1.Draw(window);
				s2.Draw(window);

				window.display();
			}
			return 0;
		};
}
