#pragma once

#include<algorithm>
#include<random>
#include<chrono>

#include "GameBoard.hpp"
#include "Tetromino.hpp"

class Game
	: public sf::Drawable
{
private:
	float side_length;
	sf::Vector2f origin;
	GameBoard board;
	std::array<Tetromino, 7> piece_bag;
	size_t index;

	std::array<Tetromino,7> create_bag()
	{
		std::array<Tetromino, 7> bag = {
			Tetromino(Tetromino::L, side_length, origin),
			Tetromino(Tetromino::J, side_length, origin),
			Tetromino(Tetromino::O, side_length, origin),
			Tetromino(Tetromino::S, side_length, origin),
			Tetromino(Tetromino::Z, side_length, origin),
			Tetromino(Tetromino::T, side_length, origin),
			Tetromino(Tetromino::I, side_length, origin),
		};
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

		shuffle(bag.begin(), bag.end(), std::default_random_engine(seed));
		
		return bag;
	}

public:
	Game(sf::Vector2f origin, float side_length)
		: side_length(side_length), origin(origin), board(24,10,origin,side_length),
		piece_bag(create_bag()), index(0)
	{  }

	void step()
	{
		if (!(board.collides(piece_bag[index].getPositionsArray(), sf::Vector2f(0, 1))))
		{
			piece_bag[index].move(sf::Vector2f(0, 1));
		}
		else {
			lock_piece();
		}
	}

	void move(sf::Vector2f direction)
	{
		if (!(board.collides(piece_bag[index].getPositionsArray(),direction)))
			piece_bag[index].move(direction);
	}

	void lock_piece()
	{
		board.place_piece(piece_bag[index]);
		index++;
		if (index == piece_bag.size())
		{
			piece_bag = create_bag();
			index = 0;
		}
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(board);
		target.draw(piece_bag[index]);
	}
};