TabContainer::Rects TabContainer::getRects() const
{
	Rects rects;
	const sf::Transform transform = getTransform();
	for (auto tab : mTabs)
	{
		sf::Vector2f rectPosition = tab->getPosition();
		sf::Vector2f rectSize = tab->getSize();
		sf::FloatRect rect(rectPosition.x, rectPosition.y, rectSize.x, rectSize.y);

		rects.emplace_back(transform.transformRect(rect));
	}

	return rects;
}