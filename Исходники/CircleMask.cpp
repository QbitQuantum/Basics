void CircleMask::updateTransform(const sf::Transform& transform)
{
	const sf::Vector2f x1(transform.transformPoint(-1.f, 0.f));
	const sf::Vector2f x2(transform.transformPoint(1.f, 0.f));
	const sf::Vector2f y1(transform.transformPoint(0.f, -1.f));
	const sf::Vector2f y2(transform.transformPoint(0.f, 1.f));

	const float scaleX = je::length(x2 - x1);
	const float scaleY = je::length(y2 - y1);

	// until we decide to handle elipses
	const float epsilon = 0.1f;
	JE_ASSERT(scaleX >= scaleY - epsilon && scaleX <= scaleY + epsilon);

	radius = originalRadius * scaleX * baseTransform.getScale().x;
	center = baseTransform.getTransform().transformPoint((x2 + x1) * 0.5f);

#ifdef JE_DEBUG
	debugCircle.setRadius(radius);
	debugCircle.setOrigin(radius, radius);
	debugCircle.setPosition(center);
#endif
}