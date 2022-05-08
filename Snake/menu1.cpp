#include "Menu.h"

bool menu() {
	Button bt("menu.png", 233, 105, 150, 50, 50, 3);
	RenderWindow window(bt.RenWin(), "Snake", Style::None);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	Image icon;
	icon.loadFromFile("images/icon.png");
	window.setIcon(32, 32, icon.getPixelsPtr());
	Texture aboutTexture;
	aboutTexture.loadFromFile("images/btn.png");
	Sprite about(aboutTexture);
	about.setPosition(40, 80);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear(Color(50, 50, 50));

		if (Mouse::isButtonPressed(Mouse::Left))
			switch (bt.mouseTrack(window)) {
			case 1: return true; window.close(); break;
			case 2: window.draw(about); window.display(); while (Mouse::isButtonPressed(Mouse::Left)); break;
			case 3: return false; window.close(); break;
			};

		bt.Draw(window);
		window.display();
	}
};