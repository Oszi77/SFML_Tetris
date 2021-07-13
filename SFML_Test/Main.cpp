#include "SFML/Graphics.hpp"
#include <time.h>

const int M = 20, N = 10;

int field[M][N] = { 0 };//M, N k�tdimenzi�s t�mb, aminek minden eleme 0 -a.

//Pontok objektuma, �s k�t 4 elem� Point t�pus� t�mb.
struct Point{
	int x, y;
} a[4], b[4];



//A tetris form�i.
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
	//Ablak objektum l�trehoz�sa �s konstruktor be�ll�t�sai
	sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");

	sf::Texture t;//Text�ra objektum
	t.loadFromFile("img/tiles.png");//Bit�rk�p f�jl hozz�ad�sa a tektt�r�hoz.

	sf::Sprite s(t);//PNG sprite objktum a text�r�val fel�p�tve.
	//A text�r�b�l a spritol� ter�let megad�sa.
	s.setTextureRect(sf::IntRect(0, 0, 18, 18));

	int dx = 0;//X ir�ny� elmozd�t�s.
	bool rotate = false; //Elforgat�s van-e?
	int colorNum = 1;//A n�gyzet sz�ne.

	float timer = 0, delay = 0.3;

	sf::Clock clock;

	//J�t�k loop.
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		timer += time;

		sf::Event e;//Esem�ny figyel�/kezel� objektum l�trehoz�sa.
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

			/// Mozgat�s ///
			for (int i = 0; i < 4; i++) {
				b[i] = a[i];
				a[i].x += dx;
			}
			if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];


			/// Forgat�s /// 
			if (rotate)
			{
				Point p = a[1];//Az elforgat�s k�z�ppontja.
				for (int i = 0; i < 4; i++)
				{
					int x = a[i].y - p.y;
					int y = a[i].x - p.x;
					a[i].x = p.x - x;
					a[i].y = p.y + y;
				}
				if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
			}
			 /// Peri�dus/friss�t�s/y ir�ny� tick ///
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
		/// sorok �llapot�nak vizsg�lata///
		
		
		dx = 0; rotate = false; delay = 0.3;

		window.clear(sf::Color::Yellow);//H�tt�r sz�n be�ll�t�sa.

		/// Kirajzol�s ///
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0) continue;
				s.setTextureRect(sf::IntRect(field[i][j]*18, 0, 18, 18));
				//A sprite egyik sz�n� kock�ja az �bra t�rk�p x helye*18 px-el, mivel ekkora egy n�gyzet m�rete.
				s.setPosition(j * 18, i * 18);
				window.draw(s);//A sprite kirajzol�sa.
			}
		}

		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(sf::IntRect(colorNum * 18, 0, 18, 18));
			s.setPosition(a[i].x * 18, a[i].y * 18);
			window.draw(s);
		}
		
		window.display();//Ablak megjelen�t�se.


	}

	return 0;
}