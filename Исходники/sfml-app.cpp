int main()
{
	sf::RenderWindow window;
	sf::Texture circle_texture;
	sf::Sprite circle;
	sf::Clock clock;
	sf::Vector2f circle_position;
	sf::Vector2i mouse_position;
	sf::Vector2i destination;

	bool stop_circle = true;
	float angle;
	float move_x;
	float move_y;
	float distance;
	float distance_x;
	float distance_y;

	window.create(sf::VideoMode(WIDTH, HEIGHT), "SFML Movement");

	if (!circle_texture.loadFromFile("circle.png"))
		std::cout << "Error: could not load player image" << std::endl;

	circle.setTexture(circle_texture);
	circle.setOrigin(16, 16);
	circle.setPosition(WIDTH/2, HEIGHT/2);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Right)
					{
						stop_circle = false;
						destination = sf::Mouse::getPosition(window);

						// get the angle between the circle and mouse click using arc tangent
						angle = atan2(destination.y - circle_position.y, destination.x - circle_position.x);
					}
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::S)
					{
						stop_circle = true;
					}
					break;
			}
		}

		// Vector to hold circle position
		circle_position = circle.getPosition();

		// Current mouse position
		mouse_position = sf::Mouse::getPosition(window);

		// Distance
		distance_x = destination.x - circle_position.x;
		distance_y = destination.y - circle_position.y;
		distance = sqrt(distance_x * distance_x + distance_y * distance_y);

		// Frames and movement
		if (stop_circle == false)
		{
			move_x = cos(angle);
			move_y = sin(angle);

			circle.move(move_x, move_y);

			if (distance < 2)
				stop_circle = true;
		}
		//test
		system("clear");
		std::cout << "Circle X: " << circle_position.x << " Circle Y: " << circle_position.y << std::endl;
		std::cout << "Mouse X: " << mouse_position.x << " Mouse Y: " << mouse_position.y << std::endl;
		std::cout << "Destination " << destination.x << ", " << destination.y << std::endl;
		std::cout << "Angle: " << angle * 180 / PI << std::endl;
		std::cout << "move_x: " << move_x << " move_y: " << move_y << std::endl;
		float x = destination.x - circle_position.x;
		float y = destination.y - circle_position.y;
		std::cout << "Distance: " << sqrt(x * x + y * y) << std::endl;

		window.draw(circle);
		window.display();
		window.clear();
	}
}