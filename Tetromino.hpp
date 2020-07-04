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
	sf::Vector2f location;
	sf::Vector2f origin;

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

	std::array<sf::Vector2f, 4> getPositions(type piece_type)
	{
		std::array<sf::Vector2f, 4> positions;
		switch (piece_type)
		{
		case type::L:
			return { sf::Vector2f(0,1),sf::Vector2f(1,1),sf::Vector2f(2,1),sf::Vector2f(2,0) };
		case type::J:
			return { sf::Vector2f(0,0),sf::Vector2f(0,1),sf::Vector2f(1,1),sf::Vector2f(2,1) };
		case type::O:
			return { sf::Vector2f(0,0),sf::Vector2f(0,1),sf::Vector2f(1,0),sf::Vector2f(1,1) };
		case type::S:
			return { sf::Vector2f(0,1),sf::Vector2f(1,1),sf::Vector2f(1,0),sf::Vector2f(2,0) };
		case type::Z:
			return { sf::Vector2f(0,0),sf::Vector2f(1,0),sf::Vector2f(1,1),sf::Vector2f(2,1) };
		case type::T:
			return { sf::Vector2f(0,1),sf::Vector2f(1,1),sf::Vector2f(2,1),sf::Vector2f(1,0) };
		case type::I:
			return { sf::Vector2f(0,0),sf::Vector2f(1,0),sf::Vector2f(2,0),sf::Vector2f(3,0) };
		
		
		}
		return positions;
	}
	

public:
	Tetromino(type piece_type, float side_length, sf::Vector2f origin)
		: side_length(side_length), piece_type(piece_type), border_length(1),
		squares{ std::make_unique<Square>(getTetColor(piece_type),side_length), std::make_unique<Square>(getTetColor(piece_type),side_length),
				 std::make_unique<Square>(getTetColor(piece_type),side_length), std::make_unique<Square>(getTetColor(piece_type),side_length) },
		square_positions(getPositions(piece_type)), origin(origin), location(3.f,0.f)
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

	std::array<std::unique_ptr<Square>, 4> getSquaresArray()
	{
		return std::move(squares);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (int i = 0; i < 4; i++)
		{
			squares[i]->setPosition(origin + side_length*(square_positions[i] + location));
			target.draw(*squares[i]);
		}
	}

};