#pragma once
#include <SFML/Graphics.hpp>

class Square 
	: public sf::RectangleShape
{
public:
	enum Color{cyan, yellow, purple, green, blue, red, orange, white};
private:
	Color color;
	float side_length;

	sf::Color getColorToSf() const
	{
		switch (color)
		{
		case Color::cyan:
			return sf::Color::Cyan;
		case Color::yellow:
			return sf::Color::Yellow;
		case Color::purple:
			return sf::Color(153, 50, 204);
		case Color::green:
			return sf::Color::Green;
		case Color::blue:
			return sf::Color::Blue;
		case Color::red:
			return sf::Color::Red;
		case Color::orange:
			return sf::Color(255, 140, 0);
		default:
			return sf::Color::White;
		}
	}

public:
	Square(Color color, float side_length)
		: color(color), side_length(side_length), RectangleShape(sf::Vector2f(side_length,side_length))
	{
		this->setFillColor(getColorToSf());
		this->setOutlineColor(sf::Color::Black);
		this->setOutlineThickness(-2);
	}


};