bool CollisionCell::checkCollisionsWithin(std::vector<WorldObject *> *_outputCollisions, sf::FloatRect _bounds)
{
	bool collision = false;

	for (unsigned int i = 0; i < m_TouchingWorldObjects.size(); i += 1)
	{
		if (_bounds.intersects(m_TouchingWorldObjects.at(i)->getBounds()))
		{
			bool present = false;

			for (unsigned int j = 0; j < _outputCollisions->size(); j += 1)
			{
				if (_outputCollisions->at(j) == m_TouchingWorldObjects.at(i))
				{
					present = true;
					break;
				}
			}

			if (!present)
			{
				collision = true;
				_outputCollisions->push_back(m_TouchingWorldObjects.at(i));
			}
		}
	}

	return collision;
}