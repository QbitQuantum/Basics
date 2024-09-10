void NotificationManager::update(sf::Time dt)
{
	if(notifications.size() == 0)
		return;

	sf::Text tmpText;
	tmpText.setCharacterSize(50);
	tmpText.setFont(NotificationFont);

	auto factor = (static_cast<float>(RenderWindow.getView().getSize().y) / RenderWindow.getSize().y);

	if(notifications[0].time > 0)
		notifications[0].time -= dt.asSeconds();					//Count down notification time
	else if(notifications[0].alpha - dt.asSeconds() * 150.f > 0)
		notifications[0].alpha -= dt.asSeconds() * 150.f;			//Hide notification
	else
		notifications.erase(this->notifications.begin());			//Delete notification

	for(auto i = 0u; i < notifications.size() && i < 5; i++)
	{
		/* Apply alpha to text and notification */
		tmpText.setFillColor
		({
			notificationTextColor.r,
			notificationTextColor.g,
			notificationTextColor.b,
			static_cast<sf::Uint8>(sfm::mapValue(notifications[i].alpha, 0.f, static_cast<float>(notificationBacgroundColor.a), 0.f, static_cast<float>(notificationTextColor.a)))
		 });
		notifications[i].background.setFillColor
		({
			notificationBacgroundColor.r,
			notificationBacgroundColor.g,
			notificationBacgroundColor.b,
			static_cast<sf::Uint8>(notifications[i].alpha)
		 });

		/* Set notification's background position */
		notifications[i].background.setScale(factor, factor);
		notifications[i].background.setPosition(RenderWindow.mapPixelToCoords({static_cast<int>(RenderWindow.getSize().x - 410), static_cast<int>(10 + i * 50)}));

		/* Set text parameters */
		tmpText.setScale(factor, factor);
		tmpText.setString(notifications[i].text);
		tmpText.setPosition(RenderWindow.mapPixelToCoords({static_cast<int>(RenderWindow.getSize().x - 410 + 10), static_cast<int>(10 + i * 50 - 15)}));

		/* Draw notification */
		RenderWindow.draw(notifications[i].background);
		RenderWindow.draw(tmpText);
	}
}