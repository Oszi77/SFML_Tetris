#include "SFML/Graphics.hpp"

int main() {

	sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");
	sf::Event e;

	sf::Texture t;
	t.loadFromFile("img/tiles.png");

	sf::Sprite s(t);
	s.setTextureRect(sf::IntRect(0, 0, 18, 18));

	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::Yellow);
		window.draw(s);
		window.display();


	}

	return 0;
}