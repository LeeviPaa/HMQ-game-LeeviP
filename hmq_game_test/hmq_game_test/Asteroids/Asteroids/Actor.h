#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

/*TODO:
can be drawn
can be created
can be destroyed
Has a position
Has scale
Has rotation
*/

class Actor: public Transformable, public Drawable
{
protected:
	float VectorLenght(sf::Vector2f Vector);
	int VectorLenght(sf::Vector2i Vector);


public:
	Actor();
	~Actor();

	virtual void Update(Time deltaTime);

	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();

		//sf::CircleShape shape(25.f);

		sf::Vector2<float> boxSize;
		boxSize.x = 25;
		boxSize.y = 25;

		//no need to do this every frame!!!
		//create a start() function
		sf::RectangleShape shape(boxSize);
		shape.setFillColor(sf::Color::Blue);

		target.draw(shape, states);
	}
};

