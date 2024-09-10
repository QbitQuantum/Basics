void Fruit::Draw(sf::RenderTarget& target, sf::Transform const& transform)
{
    if (m_Visible)
    {
        sf::Vector2f const pos = transform.transformPoint(m_Position);
        m_Sprite.SetPosition(pos);
        m_Sprite.Draw(target);
    }
}