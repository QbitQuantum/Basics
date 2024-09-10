	void drawFpsCounter(sf::RenderWindow& aWindow, const sf::Font& aFont, sf::Time aDeltaTime)
	{
		sf::Text text;
		text.setFont(aFont);
		text.setColor(sf::Color::Red);
		text.setPosition(0, 50.0f);

		char buffer[Int64TextWidth];
		_i64toa_s(aDeltaTime.asMicroseconds(), buffer, Int64TextWidth, 10);
		//_gcvt_s(buffer, Int64TextWidth, elapsedTime, 20);

		text.setString(buffer);

		aWindow.draw(text);
	}