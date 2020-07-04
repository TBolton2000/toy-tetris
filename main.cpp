#include <SFML/Graphics.hpp>
#include <vector>

#include "Tetromino.hpp"
#include "GameBoard.hpp"
#include "Game.hpp"

int main()
{

	float side_length = 30.f;
	int screen_width = static_cast<int>(20*side_length);
	int screen_height = static_cast<int>(800.f*side_length / 30.f);
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Trevor Tetris");
	window.setFramerateLimit(60);
	int x_pos = 0;
	int y_pos = 0;
	int frame_count = 0;
	int time_delta = 120;
	sf::Vector2f origin((screen_width - side_length * 10) / 2, (screen_height - side_length * 24) / 2);
	Tetromino piece(Tetromino::type::L, side_length, origin);

	sf::RectangleShape gameBackground(sf::Vector2f(side_length * 10, side_length * 24));
	gameBackground.setOutlineColor(sf::Color(220, 220, 220));
	gameBackground.setOutlineThickness(10);
	gameBackground.setPosition(origin);

	sf::RectangleShape time_dial(sf::Vector2f(30.f, 10.f));
	time_dial.setOutlineColor(sf::Color::White);
	time_dial.setOutlineThickness(2);
	time_dial.setPosition(origin - sf::Vector2f(50, 0));
	
	sf::RectangleShape time_fill(sf::Vector2f(0.f, 10.f));
	time_fill.setFillColor(sf::Color::Blue);
	time_fill.setPosition(origin - sf::Vector2f(50, 0));

	Game game(origin, side_length);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				if (event.key.code == sf::Keyboard::A)
					game.move(sf::Vector2f(-1.f, 0.f));
				if (event.key.code == sf::Keyboard::D)
					game.move(sf::Vector2f(1.f, 0.f));
				if (event.key.code == sf::Keyboard::S)
				{
					frame_count = 0;
				}
				if (event.key.code == sf::Keyboard::Q)
					game.rotate(1);
				if (event.key.code == sf::Keyboard::E)
					game.rotate(-1);
			}
		}

		if (frame_count % time_delta == 1)
			game.step();

		time_fill.setSize(sf::Vector2f(frame_count % time_delta / static_cast<float>(time_delta) * 30.f, 10.f));

		++frame_count;

		window.clear();

		window.draw(gameBackground);
		window.draw(time_dial);
		window.draw(time_fill);
		window.draw(game);

		window.display();
	}

	return 0;
}