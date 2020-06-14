#include "pch.h"
#include "GameTable.h"
#include "BrickPile.h"
#include <vector>
#include <windows.h>

using namespace sf;
using namespace std;


GameTable::GameTable()
{
	RenderWindow app(VideoMode(800, 600), "XNX");
	menu(app);
}


void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/start.png");
	menuTexture2.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/about.png");
	menuTexture3.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/exit.png");
	aboutTexture.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/Pasha.jpg");
	menuBackground.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/menu.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(40, 120);
	menu2.setPosition(40, 450);
	menu3.setPosition(40, 500);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(40, 120, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(40, 450, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(40, 500, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { 
				isMenu = false;
				window.close();
				GameRun();
			}

			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }
		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.display();
	}
}


bool isCollide(Sprite s1, Sprite s2) {
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}


void GameRun() {
	BrickPile BP;
	int HP;
	cout << "HP: ";
	cin >> HP;

	HP--;

	PuckSupply PS(HP);
	RenderWindow app(VideoMode(800, 600), "XNX");
	app.setFramerateLimit(60);
	Texture brick, BG, paddle, puck;

	brick.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/brick_2_3.png");
	BG.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/background.jpg");
	paddle.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/paddle.png");
	puck.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/puck.png");

	Sprite Puck(puck);
	Sprite Paddle(paddle);
	Sprite background(BG);
	Sprite block[1000];

	Puck.setPosition(330, 540);
	Paddle.setPosition(300, 580);

	float dx_Paddle = 6;
	bool pusk = true;
	float dx_Puck = 0;
	float dy_Puck = 0;

	int n = 0;
	int n1;

	for (int i = 1; i <= BP._bricks_x; i++) {
		for (int j = 2; j <= BP._bricks_y+1; j++) {
			block[n].setTexture(brick);
			block[n].setPosition(i * 63, j * 30);
			n++;
		}
	}

	n1 = n;

	while (app.isOpen()) {
		Event e;
		while (app.pollEvent(e)) {
			if (e.type == Event::Closed) {
				app.close();
			}
		}

		Puck.move(dx_Puck, 0);
		for (int i = 0; i <= n; i++) {
			if (isCollide(block[i], Puck)) {
				block[i].setPosition(-100, 0);
				dx_Puck = -dx_Puck;
				--n1;
			}
		}

		Puck.move(0, dy_Puck);
		for (int i = 0; i <= n; i++) {
			if (isCollide(block[i], Puck)) {
				block[i].setPosition(-100, 0);
				dy_Puck = -dy_Puck;
				--n1;
			}
		}

		Vector2f a = Puck.getPosition();

		if (a.x < 0 || a.x > 770) dx_Puck = -dx_Puck;
		if (a.y < 0 || a.y > 560) dy_Puck = -dy_Puck;

		Vector2f b = Paddle.getPosition();

		if (n1 == 0) { app.close(); GameWin(); }
		if (a.y > 560) 
		{ 
			if (HP < 1)
			{
				app.close();
				GameLose();
			}

			PS.getPuck();
			HP--;
			dx_Puck = 0;
			dy_Puck = 0;
			Puck.setPosition(330, 540);
			Paddle.setPosition(300, 580);
			pusk = true;
		} 

		if (Keyboard::isKeyPressed(Keyboard::Right)) Paddle.move(dx_Paddle, 0);
		if (Keyboard::isKeyPressed(Keyboard::Left)) Paddle.move(-dx_Paddle, 0);
		if (Keyboard::isKeyPressed(Keyboard::Space)) Sleep(20000000); 


		if ((pusk == true) and (Keyboard::isKeyPressed(Keyboard::Up)))
		{
			dx_Puck = 0;
			dy_Puck = 2;
			Puck.move(dx_Puck, 0);
			Puck.move(0, dy_Puck);
			pusk = false;
			dx_Puck = 3;
		}

		if ((pusk == true) and (Keyboard::isKeyPressed(Keyboard::Right)))
		{
			if (a.x < 760) {
				Puck.move(dx_Paddle, 0);
			}
		}

		if ((pusk == true) and (Keyboard::isKeyPressed(Keyboard::Left)))
		{
			if (a.x > 0) {
				Puck.move(-dx_Paddle, 0);
			}
		}

		if (b.x > 705) {
			Paddle.move(-dx_Paddle, 0);
		}

		if (b.x < 0) {
			Paddle.move(dx_Paddle, 0);
		}

		if (isCollide(Paddle, Puck)) {
			dy_Puck = -dy_Puck;
		}

		app.clear();
		app.draw(background);
		app.draw(Puck);
		app.draw(Paddle);

		for (int i = 0; i < n; i++) {
			app.draw(block[i]);
		}

		app.display();
	}
}


void GameWin() {
	RenderWindow app(VideoMode(800, 600), "You win!");
	Texture BG;

	BG.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/win.png");

	Sprite Background(BG);

	while (app.isOpen()) {
		Event e;
		while (app.pollEvent(e)) {
			if (e.type == Event::Closed) {
				app.close();
			}
		}

		app.clear();
		app.draw(Background);
		app.display();
	}
}


void GameLose() {
	RenderWindow app(VideoMode(800, 600), "You lose!");
	Texture BG;

	BG.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/lose.png");

	Sprite Background(BG);

	while (app.isOpen()) {
		Event e;
		while (app.pollEvent(e)) {
			if (e.type == Event::Closed) {
				app.close();
			}
		}

		app.clear();
		app.draw(Background);
		app.display();
	}
}

GameTable::~GameTable()
{
}
