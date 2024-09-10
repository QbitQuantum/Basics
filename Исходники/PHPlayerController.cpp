//private
sf::Vector3f PlayerController::getManifold(const sf::FloatRect& worldRect)
{
    sf::FloatRect overlap;
    sf::FloatRect playerBounds = m_entity->getComponent<lm::CollisionComponent>()->globalBounds();

    //we know we intersect, but we want the overlap
    worldRect.intersects(playerBounds, overlap);
    auto collisionNormal = sf::Vector2f(worldRect.left + (worldRect.width / 2.f), worldRect.top + (worldRect.height / 2.f)) - m_entity->getPosition();

    sf::Vector3f manifold;

    if (overlap.width < overlap.height)
    {
        manifold.x = (collisionNormal.x < 0) ? 1.f : -1.f;
        manifold.z = overlap.width;
    }
    else
    {
        manifold.y = (collisionNormal.y < 0) ? 1.f : -1.f;
        manifold.z = overlap.height;
    }

    return manifold;
}