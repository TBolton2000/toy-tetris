#include <SFML/Graphics.hpp>
#include <vector>

int main()
{

	int screen_width = 600;
	int screen_height = 800;
	sf::RenderWindow window(sf::VideoMode(600, 800), "Trevor Tetris");
	window.setFramerateLimit(60);
	float side_length = 30.f;
	int x_pos = 0;
	int y_pos = 0;
	std::vector<sf::RectangleShape> tetris_piece;
	for (int i = 0; i < 4; i++) {
		tetris_piece.emplace_back(sf::Vector2f(side_length, side_length));
		tetris_piece[i].setOrigin(-1*(screen_width - side_length * 10) / 2, -1*(screen_height - side_length * 24) / 2);
		tetris_piece[i].setPosition(x_pos * side_length, y_pos * side_length + side_length*i);
		tetris_piece[i].setFillColor(sf::Color::Blue);
	}

	sf::RectangleShape game_board(sf::Vector2f(side_length * 10, side_length * 24));
	game_board.setPosition((screen_width - side_length * 10) / 2, (screen_height - side_length * 24) / 2);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::A && x_pos > 0)
					x_pos--;
				if (event.key.code == sf::Keyboard::D && x_pos < 9)
					x_pos++;
				if (event.key.code == sf::Keyboard::W && y_pos > 0)
					y_pos--;
				if (event.key.code == sf::Keyboard::S && y_pos < 23)
					y_pos++;
			}
		}

		window.clear();

		for (int i = 0; i < 4; i++) {
			tetris_piece[i].setPosition(x_pos * side_length, y_pos * side_length + side_length * i);
		}

		window.draw(game_board);

		for (auto part : tetris_piece)
			window.draw(part);

		window.display();
	}

	return 0;
}