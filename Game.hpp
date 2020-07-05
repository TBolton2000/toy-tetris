#pragma once

#include<algorithm>
#include<random>
#include<chrono>
#include<math.h>

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

	sf::Vector2f try_to_kick(int rot_direction, std::array<sf::Vector2f, 4> square_positions)
	{
		int curr_rot_state = piece_bag[index].getRotationState();
		int next_rot_state;
		if (rot_direction == 1)
			next_rot_state = (curr_rot_state + 1) % 4;
		else /*if (rot_direction == -1)*/
			next_rot_state = (curr_rot_state + 3) % 4;

		if (piece_bag[index].getPieceType() != Tetromino::I)
		{
			if (curr_rot_state == 0)
			{
				if (next_rot_state == 1)
				{
					if (!(board.collides(square_positions, sf::Vector2f(-1, 0))))
					{
						return sf::Vector2f(-1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-1, -1))))
					{
						return sf::Vector2f(-1, -1);
					}
					if (!(board.collides(square_positions, sf::Vector2f(0, 2))))
					{
						return sf::Vector2f(0, 2);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-1, 2))))
					{
						return sf::Vector2f(-1, 2);
					}
					return sf::Vector2f(0, 0);
				}
				else /*if (next_rot_state == 3)*/
				{
					if (!(board.collides(square_positions, sf::Vector2f(1, 0))))
					{
						return sf::Vector2f(1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(1, -1))))
					{
						return sf::Vector2f(1, -1);
					}
					if (!(board.collides(square_positions, sf::Vector2f(0, 2))))
					{
						return sf::Vector2f(0, 2);
					}
					if (!(board.collides(square_positions, sf::Vector2f(1, 2))))
					{
						return sf::Vector2f(1, 2);
					}
					return sf::Vector2f(0, 0);
				}
			}
			else if (curr_rot_state == 1)
			{
				if (next_rot_state == 2)
				{
					if (!(board.collides(square_positions, sf::Vector2f(1, 0))))
					{
						return sf::Vector2f(1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(1, 1))))
					{
						return sf::Vector2f(1, 1);
					}
					if (!(board.collides(square_positions, sf::Vector2f(0, -2))))
					{
						return sf::Vector2f(0, -2);
					}
					if (!(board.collides(square_positions, sf::Vector2f(1, -2))))
					{
						return sf::Vector2f(1, -2);
					}
					return sf::Vector2f(0, 0);
				}
				else /*if (next_rot_state == 0)*/
				{
					if (!(board.collides(square_positions, sf::Vector2f(1, 0))))
					{
						return sf::Vector2f(1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(1, 1))))
					{
						return sf::Vector2f(1, 1);
					}
					if (!(board.collides(square_positions, sf::Vector2f(0, -2))))
					{
						return sf::Vector2f(0, -2);
					}
					if (!(board.collides(square_positions, sf::Vector2f(1, -2))))
					{
						return sf::Vector2f(1, -2);
					}
					return sf::Vector2f(0, 0);
				}
			}
			else if (curr_rot_state == 2)
			{
				if (next_rot_state == 3)
				{
					if (!(board.collides(square_positions, sf::Vector2f(1, 0))))
					{
						return sf::Vector2f(1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(1, -1))))
					{
						return sf::Vector2f(1, -1);
					}
					if (!(board.collides(square_positions, sf::Vector2f(0, 2))))
					{
						return sf::Vector2f(0, 2);
					}
					if (!(board.collides(square_positions, sf::Vector2f(1, 2))))
					{
						return sf::Vector2f(1, 2);
					}
					return sf::Vector2f(0, 0);
				}
				else /*if (next_rot_state == 1)*/
				{
					if (!(board.collides(square_positions, sf::Vector2f(-1, 0))))
					{
						return sf::Vector2f(-1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-1, -1))))
					{
						return sf::Vector2f(-1, -1);
					}
					if (!(board.collides(square_positions, sf::Vector2f(0, 2))))
					{
						return sf::Vector2f(0, 2);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-1, 2))))
					{
						return sf::Vector2f(-1, 2);
					}
					return sf::Vector2f(0, 0);
				}
			}
			else if (curr_rot_state == 3)
			{
				if (next_rot_state == 2)
				{
					if (!(board.collides(square_positions, sf::Vector2f(-1, 0))))
					{
						return sf::Vector2f(-1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-1, 1))))
					{
						return sf::Vector2f(-1, 1);
					}
					if (!(board.collides(square_positions, sf::Vector2f(0, -2))))
					{
						return sf::Vector2f(0, -2);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-1, -2))))
					{
						return sf::Vector2f(-1, -2);
					}
					return sf::Vector2f(0, 0);
				}
				else /*if (next_rot_state == 0)*/
				{
					if (!(board.collides(square_positions, sf::Vector2f(-1, 0))))
					{
						return sf::Vector2f(-1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-1, 1))))
					{
						return sf::Vector2f(-1, 1);
					}
					if (!(board.collides(square_positions, sf::Vector2f(0, -2))))
					{
						return sf::Vector2f(0, -2);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-1, -2))))
					{
						return sf::Vector2f(-1, -2);
					}
					return sf::Vector2f(0, 0);
				}
			}
		}
		else /*if (piece_bag[index].getPieceType() == Tetromino::I)*/
		{
			if (curr_rot_state == 0)
			{
				if (next_rot_state == 1)
				{
					if (!(board.collides(square_positions, sf::Vector2f(-2, 0))))
					{
						return sf::Vector2f(-2, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(1, 0))))
					{
						return sf::Vector2f(1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-2, 1))))
					{
						return sf::Vector2f(-2, 1);
					}
					if (!(board.collides(square_positions, sf::Vector2f(1, -2))))
					{
						return sf::Vector2f(1, -2);
					}
					return sf::Vector2f(0, 0);
				}
				else /*if (next_rot_state == 3)*/
				{
					if (!(board.collides(square_positions, sf::Vector2f(-1, 0))))
					{
						return sf::Vector2f(-1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(2, 0))))
					{
						return sf::Vector2f(2, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-1, -2))))
					{
						return sf::Vector2f(-1, -2);
					}
					if (!(board.collides(square_positions, sf::Vector2f(2, 1))))
					{
						return sf::Vector2f(2, 1);
					}
					return sf::Vector2f(0, 0);
				}
			}
			else if (curr_rot_state == 1)
			{
				if (next_rot_state == 2)
				{
					if (!(board.collides(square_positions, sf::Vector2f(-1, 0))))
					{
						return sf::Vector2f(-1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(2, 0))))
					{
						return sf::Vector2f(2, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-1, -2))))
					{
						return sf::Vector2f(-1, -2);
					}
					if (!(board.collides(square_positions, sf::Vector2f(2, 1))))
					{
						return sf::Vector2f(2, 1);
					}
					return sf::Vector2f(0, 0);
				}
				else /*if (next_rot_state == 0)*/
				{
					if (!(board.collides(square_positions, sf::Vector2f(2, 0))))
					{
						return sf::Vector2f(2, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-1, 0))))
					{
						return sf::Vector2f(-1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(2, -1))))
					{
						return sf::Vector2f(2, -1);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-1, 2))))
					{
						return sf::Vector2f(-1, 2);
					}
					return sf::Vector2f(0, 0);
				}
			}
			else if (curr_rot_state == 2)
			{
				if (next_rot_state == 3)
				{
					if (!(board.collides(square_positions, sf::Vector2f(2, 0))))
					{
						return sf::Vector2f(2, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-1, 0))))
					{
						return sf::Vector2f(-1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(2, -1))))
					{
						return sf::Vector2f(2, -1);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-1, 2))))
					{
						return sf::Vector2f(-1, 2);
					}
					return sf::Vector2f(0, 0);
				}
				else /*if (next_rot_state == 1)*/
				{
					if (!(board.collides(square_positions, sf::Vector2f(1, 0))))
					{
						return sf::Vector2f(1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-2, 0))))
					{
						return sf::Vector2f(-2, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(1, 2))))
					{
						return sf::Vector2f(1, 2);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-2, -1))))
					{
						return sf::Vector2f(-2, -1);
					}
					return sf::Vector2f(0, 0);
				}
			}
			else if (curr_rot_state == 3)
			{
				if (next_rot_state == 2)
				{
					if (!(board.collides(square_positions, sf::Vector2f(-2, 0))))
					{
						return sf::Vector2f(-2, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(1, 0))))
					{
						return sf::Vector2f(1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-2, 1))))
					{
						return sf::Vector2f(-2, 1);
					}
					if (!(board.collides(square_positions, sf::Vector2f(1, -2))))
					{
						return sf::Vector2f(1, -2);
					}
					return sf::Vector2f(0, 0);
				}
				else /*if (next_rot_state == 0)*/
				{
					if (!(board.collides(square_positions, sf::Vector2f(1, 0))))
					{
						return sf::Vector2f(1, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-2, 0))))
					{
						return sf::Vector2f(-2, 0);
					}
					if (!(board.collides(square_positions, sf::Vector2f(1, 2))))
					{
						return sf::Vector2f(1, 2);
					}
					if (!(board.collides(square_positions, sf::Vector2f(-2, -1))))
					{
						return sf::Vector2f(-2, -1);
					}
					return sf::Vector2f(0, 0);
				}
			}
		}

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
	
	void rotate(int rot_direction)
	{
		
		auto [rotated_positions, relative_rotated_positions] = piece_bag[index].getRotatedPositionsArrays(rot_direction);
		
		if (!(board.collides(rotated_positions, sf::Vector2f(0, 0))))
		{
			piece_bag[index].setSquarePositions(relative_rotated_positions);
			if (rot_direction == 1)
				piece_bag[index].setRotationState((piece_bag[index].getRotationState() + 1) % 4);
			else
				piece_bag[index].setRotationState((piece_bag[index].getRotationState() + 3) % 4);
		}
		else {
			sf::Vector2f kick_value = try_to_kick(rot_direction, rotated_positions);
			if (kick_value != sf::Vector2f(0, 0))
			{
				piece_bag[index].setSquarePositions(relative_rotated_positions);
				piece_bag[index].move(kick_value);
				if (rot_direction == 1)
					piece_bag[index].setRotationState((piece_bag[index].getRotationState() + 1) % 4);
				else
					piece_bag[index].setRotationState((piece_bag[index].getRotationState() + 3) % 4);
			}
		}

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