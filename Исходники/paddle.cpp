void Paddle::update(sf::Time& dt){
	atEdge();
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !(_atRight)){
		_atLeft = false;
		float delta = dt.asSeconds() * _xVel;
		_paddle.move(delta, 0);
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !(_atLeft)){
		_atRight = false;
		float delta = dt.asSeconds() * _xVel;
		_paddle.move(-delta, 0);
	}
}