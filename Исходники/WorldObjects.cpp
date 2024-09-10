bool WorldObjects::Intersects(const sf::FloatRect & bounds)
{
	for (int i = 0; i < Count(); ++i)
	{
		if (bounds.intersects(objects[i]->getGlobalBounds()))
			return true;
	}
	return false;
}