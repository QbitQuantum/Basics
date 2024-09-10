void render()
{
	std::stringstream ss;
	std::deque<Point> trails, vertices;
	window->clear();
	window->setView(camera);
	window->draw(bg);
	sf::Color color(sf::Color::Red);
	sf::ConvexShape tail;
	tail.setFillColor(sf::Color(128,0,0,128));
	for(auto& creature:creatures) {
		window->draw(*creature);
	}
	for(auto& f:food) {
		fToken->setPosition(f);
		window->draw(*fToken);
	}
	ss.str("");
	ss << "Generation: " << gen;
	text->setPosition(10,10);
	text->setString(ss.str());
	window->setView(window->getDefaultView());
	window->draw(*text);
	if(frameclock.getElapsedTime().asMilliseconds()>0) {
		ss.str("");
		ss << "FPS: " << (int)1000.f/frameclock.restart().asMilliseconds();
		text->setString(ss.str());
		text->move(0,text->getLocalBounds().height);
		window->draw(*text);
	}

	window->display();
}