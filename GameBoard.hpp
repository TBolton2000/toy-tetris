#pragma once

#include<vector>
#include<iostream>

#include"Square.hpp"

class GameBoard
	: public sf::Drawable
{
private:
	size_t num_rows;
	size_t num_cols;
	float side_length;
	sf::Vector2f origin;
	std::vector<std::vector<std::unique_ptr<Square>>> squares;

public:
	GameBoard(size_t num_rows, size_t num_cols, sf::Vector2f origin, float side_length)
		: num_rows(num_rows), num_cols(num_cols), origin(origin), side_length(side_length)
	{
		for (size_t i = 0; i < num_rows; i++)
		{
			std::vector<std::unique_ptr<Square>> row;
			for (size_t j = 0; j < num_cols; j++)
			{
				row.push_back(std::unique_ptr<Square>(nullptr));
			}
			squares.push_back(std::move(row));
		}
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (size_t i = 0; i < squares.size(); i++)
		{
			for (size_t j = 0; j < squares.at(i).size(); j++)
			{
				if (squares.at(i).at(j))
				{
					Square& square = *squares.at(i).at(j);
					square.setPosition(sf::Vector2f(j*side_length+origin.x, i*side_length+origin.y));
					target.draw(square);
				}
			}
		}
	}

	void addNewSquare(size_t x_pos, size_t y_pos, Square::Color color)
	{
		squares.at(x_pos).at(y_pos) = std::make_unique<Square>(color, side_length);
	}

	bool collides(std::array<sf::Vector2f, 4> tetromino_locations, sf::Vector2f direction)
	{
		for (auto const& location : tetromino_locations)
		{
			sf::Vector2f new_location = location + direction;
			if (!(round(new_location.x) >= 0 && round(new_location.x) < num_cols && round(new_location.y) >= 0 && round(new_location.y) < num_rows))
				return true;
			if (squares.at(round(new_location.y)).at(round(new_location.x)) != nullptr)
				return true;
		}
		return false;
	}

	void place_piece(Tetromino& piece)
	{
		auto positions = piece.getPositionsArray();
		auto new_squares = piece.getSquaresArray();
		for (int i = 0; i < 4; i++)
		{
			int x_pos = round(positions[i].x);
			int y_pos = round(positions[i].y);
			std::cout << "Placing piece at: " << x_pos << ", " << y_pos << std::endl;
			squares.at(y_pos).at(x_pos) = std::move(new_squares[i]);
		}
	}
};