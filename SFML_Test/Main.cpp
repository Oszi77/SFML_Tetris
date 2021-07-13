#include "SFML/Graphics.hpp"
#include <time.h>

const int M = 20, N = 10;

int field[M][N] = { 0 };//M, N kétdimenziós tömb, aminek minden eleme 0 -a.

//Pontok objektuma, és két 4 elemû Point típusú tömb.
struct Point{
	int x, y;
} a[4], b[4];



//A tetris formái.
int figures[7][4] = {
	1,3,5,7,//I
	2,4,5,7,//Z
	3,5,4,6,//S
	3,5,4,7,//T
	2,3,5,7,//L
	3,5,7,6,//J
	2,3,4,5 //O
};

bool check() {
	for (int i = 0; i < 4; i++) {
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return false;
		else if (field[a[i].y][a[i].x]) return false;
	}
	return true;
}

int main() {

	srand(time(0));
	//Ablak objektum létrehozása és konstruktor beállításai
	sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");

	sf::Texture t;//Textúra objektum
	t.loadFromFile("img/tiles.png");//Bitérkép fájl hozzáadása a tekttúrához.

	sf::Sprite s(t);//PNG sprite objktum a textúrával felépítve.
	//A textúrából a spritoló terület megadása.
	s.setTextureRect(sf::IntRect(0, 0, 18, 18));

	int dx = 0;//X irányú elmozdítás.
	bool rotate = false; //Elforgatás van-e?
	int colorNum = 1;//A négyzet színe.

	float timer = 0, delay = 0.3;

	sf::Clock clock;

	//Játék loop.
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		timer += time;

		sf::Event e;//Esemény figyelõ/kezelõ objektum létrehozása.
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}

			if (e.type == sf::Event::KeyPressed)
				if (e.key.code == sf::Keyboard::Up) rotate = true;
				else if (e.key.code == sf::Keyboard::Left) dx = -1;
				else if (e.key.code == sf::Keyboard::Right) dx = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) delay = 0.05;

			/// Mozgatás ///
			for (int i = 0; i < 4; i++) {
				b[i] = a[i];
				a[i].x += dx;
			}
			if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];


			/// Forgatás /// 
			if (rotate)
			{
				Point p = a[1];//Az elforgatás középpontja.
				for (int i = 0; i < 4; i++)
				{
					int x = a[i].y - p.y;
					int y = a[i].x - p.x;
					a[i].x = p.x - x;
					a[i].y = p.y + y;
				}
				if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
			}
			 /// Periódus/frissítés/y irányú tick ///
			if (timer > delay) {
				for (int i = 0; i < 4; i++) { 
					b[i] = a[i];
					a[i].y += 1; 
				}
				if (!check()) {
					for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;

					colorNum = 1 + rand() % 7;
					int n = rand() % 7;
					for (int i = 0; i < 4; i++) {
						a[i].x = figures[n][i] % 2;
						a[i].y = figures[n][i] / 2;
					}
				} 
				timer = 0;
			 }
		/// sorok állapotának vizsgálata///
		
		
		dx = 0; rotate = false; delay = 0.3;

		window.clear(sf::Color::Yellow);//Háttér szín beállítása.

		/// Kirajzolás ///
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0) continue;
				s.setTextureRect(sf::IntRect(field[i][j]*18, 0, 18, 18));
				//A sprite egyik színû kockája az ábra térkép x helye*18 px-el, mivel ekkora egy négyzet mérete.
				s.setPosition(j * 18, i * 18);
				window.draw(s);//A sprite kirajzolása.
			}
		}

		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(sf::IntRect(colorNum * 18, 0, 18, 18));
			s.setPosition(a[i].x * 18, a[i].y * 18);
			window.draw(s);
		}
		
		window.display();//Ablak megjelenítése.


	}

	return 0;
}