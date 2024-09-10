void PointCollider::update (sf::Transform const & root)
{
  worldPos = root.transformPoint(localPos);
}