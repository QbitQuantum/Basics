void TEALShow::AddTransformedRectanglePoints( sf::FloatRect r, sf::Transform T, sf::Color col )
{
	Linestrip strip;
	strip.size = 5;
	strip.points.resize(strip.size); 
	strip.points[0].position = T.transformPoint( sf::Vector2f( r.left, r.top) );
	strip.points[0].color = col;
	strip.points[1].position = T.transformPoint( sf::Vector2f(r.left + r.width,  r.top ) );
	strip.points[1].color = col;
	strip.points[2].position = T.transformPoint( sf::Vector2f( r.left + r.width, r.top + r.height ));
	strip.points[2].color = col;
	strip.points[3].position = T.transformPoint( sf::Vector2f( r.left, r.top + r.height ) );
	strip.points[3].color = col;
	strip.points[4] = strip.points[0];

	LinestripList.push_back( strip);
}