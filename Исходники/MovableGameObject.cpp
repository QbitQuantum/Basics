void MovableGameObject::calculateNextPosition(const sf::Time& frameTime, sf::Vector2f& nextPos) const {
	sf::Vector2f position = getPosition();
	sf::Vector2f nextVel;
	calculateNextVelocity(frameTime, nextVel);
	nextPos.x = position.x + (nextVel.x + m_relativeVelocity.x) * frameTime.asSeconds();
	nextPos.y = position.y + (nextVel.y + m_relativeVelocity.y) * frameTime.asSeconds();
}