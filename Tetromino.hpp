#pragma once
#include <SFML/Graphics.hpp>
#include<array>
#include"Square.hpp"

class Tetromino
	: public sf::Drawable
{
public:
	enum type {L, J, O, S, Z, T, I};
private:
	std::array<std::unique_ptr<Square>, 4> squares;
	float side_length;
	float border_length;
	type piece_type;
	std::array<sf::Vector2f, 4> square_positions;
	sf::Vector2f rotation_center;
	sf::Vector2f location;
	sf::Vector2f game_board_origin;
	int rotation_state;

	Square::Color getTetColor(type piece_type)
	{
		switch (piece_type)
		{
		case type::L:
			return Square::orange;
		case type::J:
			return Square::blue;
		case type::O:
			return Square::yellow;
		case type::S:
			return Square::green;
		case type::Z:
			return Square::red;
		case type::T:
			return Square::purple;
		case type::I:
			return Square::cyan;
		default:
			return Square::white;
		}
	}

	std::array<sf::Vector2f, 4> getStartingPositions(type piece_type)
	{
		switch (piece_type)
		{
		case type::L:
			return { sf::Vector2f(0,1),sf::Vector2f(1,1),sf::Vector2f(2,1),sf::Vector2f(2,0) };
		case type::J:
			return { sf::Vector2f(0,0),sf::Vector2f(0,1),sf::Vector2f(1,1),sf::Vector2f(2,1) };
		case type::O:
			return { sf::Vector2f(1,0),sf::Vector2f(1,1),sf::Vector2f(2,0),sf::Vector2f(2,1) };
		case type::S:
			return { sf::Vector2f(0,1),sf::Vector2f(1,1),sf::Vector2f(1,0),sf::Vector2f(2,0) };
		case type::Z:
			return { sf::Vector2f(0,0),sf::Vector2f(1,0),sf::Vector2f(1,1),sf::Vector2f(2,1) };
		case type::T:
			return { sf::Vector2f(0,1),sf::Vector2f(1,1),sf::Vector2f(2,1),sf::Vector2f(1,0) };
		case type::I:
			return { sf::Vector2f(0,1),sf::Vector2f(1,1),sf::Vector2f(2,1),sf::Vector2f(3,1) };
		}
	}

	sf::Vector2f getStartingRotationCenter(type piece_type)
	{
		switch (piece_type)
		{
		case type::L:
			return sf::Vector2f(1, 1);
		case type::J:
			return sf::Vector2f(1, 1);
		case type::O:
			return sf::Vector2f(1.5, 0.5);
		case type::S:
			return sf::Vector2f(1, 1);
		case type::Z:
			return sf::Vector2f(1, 1);
		case type::T:
			return sf::Vector2f(1, 1);
		case type::I:
			return sf::Vector2f(1.5, 1.5);
		}
	}
	

public:
	Tetromino(type piece_type, float side_length, sf::Vector2f game_board_origin)
		: side_length(side_length), piece_type(piece_type), border_length(1),
		squares{ std::make_unique<Square>(getTetColor(piece_type),side_length), std::make_unique<Square>(getTetColor(piece_type),side_length),
				 std::make_unique<Square>(getTetColor(piece_type),side_length), std::make_unique<Square>(getTetColor(piece_type),side_length) },
		square_positions(getStartingPositions(piece_type)), rotation_center(getStartingRotationCenter(piece_type)), game_board_origin(game_board_origin),
		location(3.f,0.f), rotation_state(0)
	{  }

	void move(sf::Vector2f delta)
	{
		location += delta;
	}

	std::array<sf::Vector2f, 4> getPositionsArray()
	{
		std::array<sf::Vector2f, 4> new_positions;
		for (int i = 0; i < 4; i++)
		{
			new_positions[i] = square_positions[i] + location;
		}
		return new_positions;
	}

	auto getRotatedPositionsArrays(int direction)
	{
		std::array<sf::Vector2f, 4> relative_rotated_positions;
		std::array<sf::Vector2f, 4> rotated_positions;
		for (int i = 0; i < 4; i++)
		{
			auto temp = square_positions[i] - rotation_center;
			auto new_temp = sf::Vector2f( 0 - temp.y*direction, temp.x*direction);
			relative_rotated_positions[i] = new_temp + rotation_center;
			rotated_positions[i] = relative_rotated_positions[i] + location;
		}
		return std::make_tuple(rotated_positions, relative_rotated_positions);
	}
	
	void setSquarePositions(std::array<sf::Vector2f, 4> new_positions)
	{
		square_positions = new_positions;
	}

	std::array<std::unique_ptr<Square>, 4> getSquaresArray()
	{
		return std::move(squares);
	}

	int getRotationState()
	{
		return rotation_state;
	}

	void setRotationState(int new_state)
	{
		rotation_state = new_state;
	}

	type getPieceType()
	{
		return piece_type;
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (int i = 0; i < 4; i++)
		{
			squares[i]->setPosition(game_board_origin + side_length*(square_positions[i] + location));
			target.draw(*squares[i]);
		}
	}

};