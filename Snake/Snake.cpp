//#include "Snake.h"
//
//	Snake::Snake(int WinW, int WinH, String F, int Tx = 32, float S = 1, int X = 1, int Y = 1, int D = 1, int N = 1)
//	{
//		File = F;
//		tx = Tx;
//		dir = D; size = S;
//		num = N;
//		k = size * tx;
//		difW = (WinW - WIDTH_MAP * k) / 2;
//		difH = (WinH - HEIGHT_MAP * k) / 2;
//		s[0].x = difW + k / 2 + X * k;
//		s[0].y = difH + k / 2 + Y * k;
//
//		texture.loadFromFile("images/" + File);
//
//		spHead.setTexture(texture);
//		spBody.setTexture(texture);
//		spBody90.setTexture(texture);
//		spTail.setTexture(texture);
//
//		spHead.setTextureRect(IntRect(0, 32, tx, tx));
//		spBody.setTextureRect(IntRect(64, 0, tx, tx));
//		spBody90.setTextureRect(IntRect(96, 0, tx, tx));
//		spTail.setTextureRect(IntRect(32, 0, tx, tx));
//
//		spHead.setOrigin(tx / 2, tx / 2);
//		spBody.setOrigin(tx / 2, tx / 2);
//		spBody90.setOrigin(tx / 2, tx / 2);
//		spTail.setOrigin(tx / 2, tx / 2);
//
//		spHead.setScale(size, size);
//		spBody.setScale(size, size);
//		spBody90.setScale(size, size);
//		spTail.setScale(size, size);
//
//		spHead.setRotation(90 * D);
//		spHead.setPosition(s[0].x, s[0].y);
//
//		speed = false;
//
//
//		h.loadFromFile("music/heart.ogg");//загружаем в него звук
//		heart.setBuffer(h);//создаем звук и загружаем в него звук из буфера
//
//		b.loadFromFile("music/bell.ogg");
//		bell.setBuffer(b);//создаем звук и загружаем в него звук из буфера
//
//		m.loadFromFile("music/money.ogg");
//		money.setBuffer(m);//создаем звук и загружаем в него звук из буфера
//	};
//
//	int Snake::getCoordX(int n) { return s[n].x; };
//	int Snake::getCoordY(int n) { return s[n].y; };
//	int Snake::getLife() { return life; };
//	int Snake::getScore() { return score; }
//	int Snake::getNum() { return num; };
//	int Snake::getTimer() { return timer; };
//	Sprite Snake::getSprite() { return spHead; }
//	int Snake::getSpriteRotation() { return spHead.getRotation(); }
//
//
//	float Snake::spd(float gameTime) {
//		if ((speed == true) && (score > 0) && (spv > 0)) {
//			return gameTime / 2;
//		}
//		else {
//			speed = false;
//			spv = 10;
//			return gameTime;
//		}
//	};
//
//	void Snake::setDirection(int D) { dir = D; }
//
//	void Snake::Turbo() { speed = true; }
//
//	void Snake::update(Snake& sn, float time, float& gameTime)
//	{
//		timer += time;
//		if (timer > spd(gameTime)) {
//
//			timer -= spd(gameTime);
//
//			if (speed == true)
//			{
//				score--; spv--;
//				if (spv == 0 || score == 0)
//					timer = sn.getTimer();
//			}
//
//			for (int i = num; i > 0; --i)
//			{
//				s[i].x = s[i - 1].x; s[i].y = s[i - 1].y;
//			}
//
//			switch (dir)
//			{
//			case 0: s[0].y -= k; spHead.setRotation(0);  break;
//			case 1: s[0].x += k; spHead.setRotation(90); break;
//			case 2: s[0].y += k; spHead.setRotation(180); break;
//			case 3: s[0].x -= k; spHead.setRotation(270); break;
//			}
//			//std::cout << gameTime << std::endl;
//			interSnake(sn, gameTime);
//			interMap(dir, gameTime);
//		}
//	};
//
//	void Snake::deadSnake(int a, int b, float& gameTime) {
//
//		for (int i = b; i < a + num; i++) {
//
//			int m = (s[i].y - difH - k / 2) / k;
//			int t = (s[i].x - difW - k / 2) / k;
//
//			if (TileMap[m][t] != 'o')
//				TileMap[m][t] = 'o';
//
//			s[i].x = -32; s[i].y = -32;
//		};
//
//		num = 1;
//
//		do {
//			a = 1 + (rand() % (HEIGHT_MAP - 3));
//			b = 1 + (rand() % (WIDTH_MAP - 2));
//		} while ((TileMap[a][b] == 's'));
//
//
//		s[0].x = b * k + k / 2 + difW;
//		s[0].y = a * k + k / 2 + difH;
//		gameTime = 1000;
//		score = 0;
//		life--;
//		bell.play();
//	};
//
//	void Snake::interSnake(Snake& sn, float& gameTime) {
//		if ((s[0].x == sn.getCoordX(0)) && (s[0].y == sn.getCoordY(0))) {
//			if (num == sn.getNum())
//			{
//				sn.deadSnake(0, 0, gameTime); deadSnake(1, 1, gameTime);  return;
//			}
//			else {
//				if (num < sn.getNum())
//				{
//					deadSnake(1, 1, gameTime); return;
//				}
//				else { sn.deadSnake(0, 0, gameTime); return; }
//			}
//		}
//
//		for (int g = 1; g < sn.getNum(); g++)
//			if ((s[0].x == sn.getCoordX(g)) && (s[0].y == sn.getCoordY(g))) {
//				deadSnake(1, 1, gameTime);
//				return;
//			}
//
//
//		for (int g = 1; g < num; g++)
//			if ((s[0].x == s[g].x) && (s[0].y == s[g].y)) {
//				deadSnake(0, 1, gameTime);
//				return;
//			}
//	}
//
//	void Snake::interMap(int D, float& gameTime) {
//		int i = (s[0].y - difH - k / 2) / k;
//		int j = (s[0].x - difW - k / 2) / k;
//		{
//			if (TileMap[i][j] == 's') {
//				deadSnake(1, 1, gameTime);
//				return;
//			}
//
//			if (TileMap[i][j] == 'o') {
//				int a, b;
//				do {
//					a = 1 + (rand() % (HEIGHT_MAP - 3));
//					b = 1 + (rand() % (WIDTH_MAP - 2));
//				} while ((TileMap[a][b] == 'o') || (TileMap[a][b] == 's') || (TileMap[a][b] == 'h'));
//				TileMap[i][j] = ' ';
//				TileMap[a][b] = 'o';
//
//				if (rand() % 5 == 1) {
//					do {
//						a = 1 + (rand() % (HEIGHT_MAP - 3));
//						b = 1 + (rand() % (WIDTH_MAP - 2));
//					} while ((TileMap[a][b] == 'o') || (TileMap[a][b] == 's') || (TileMap[a][b] == 'h'));
//					TileMap[a][b] = 'h';
//				}
//				score++;
//				num++;
//				money.play();
//				return;
//			}
//
//			if (TileMap[i][j] == 'h') {
//				TileMap[i][j] = ' ';
//				life++;
//				score += 5;
//				heart.play();
//				return;
//			}
//
//		}
//	};
//
//	void Snake::Draw(RenderWindow & window) {
//		spHead.setTextureRect(IntRect(0, 32, tx, tx));
//		if (num > 1) {
//			spHead.setTextureRect(IntRect(0, 0, tx, tx));
//			for (int i = 1; i < num; i++) {
//				if (i == num - 1) {
//					if (s[i - 1].x > s[i].x)
//						spTail.setRotation(270);
//					if (s[i - 1].x < s[i].x)
//						spTail.setRotation(90);
//					if (s[i - 1].y > s[i].y)
//						spTail.setRotation(0);
//					if (s[i - 1].y < s[i].y)
//						spTail.setRotation(180);
//					spTail.setPosition(s[i].x, s[i].y);
//					window.draw(spTail);
//				}
//				else {
//					if ((s[i - 1].x != s[i + 1].x) && (s[i - 1].y != s[i + 1].y)) {
//						if (s[i - 1].x > s[i].x)
//							if (s[i].y > s[i + 1].y)
//								spBody90.setRotation(270);
//							else
//								spBody90.setRotation(0);
//						if (s[i - 1].x < s[i].x)
//							if (s[i].y > s[i + 1].y)
//								spBody90.setRotation(180);
//							else
//								spBody90.setRotation(90);
//						if (s[i - 1].y > s[i].y)
//							if (s[i].x > s[i + 1].x)
//								spBody90.setRotation(90);
//							else
//								spBody90.setRotation(0);
//						if (s[i - 1].y < s[i].y)
//							if (s[i].x > s[i + 1].x)
//								spBody90.setRotation(180);
//							else
//								spBody90.setRotation(270);
//
//						spBody90.setPosition(s[i].x, s[i].y);
//						window.draw(spBody90);
//					}
//					else {
//						if (s[i - 1].x != s[i].x)
//							spBody.setRotation(90);
//						if (s[i - 1].y != s[i].y)
//							spBody.setRotation(0);
//						spBody.setPosition(s[i].x, s[i].y);
//						window.draw(spBody);
//					}
//				}
//
//			}
//		}
//		spHead.setPosition(s[0].x, s[0].y);
//		window.draw(spHead);
//	};