float GameTime::getTime()
{
	static sf::Clock gameTime;

	sf::Time time = gameTime.getElapsedTime();
	return (time.asSeconds());
}