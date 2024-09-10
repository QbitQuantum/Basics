sf::FloatRect Ring::getGlobalBounds() const
{
    if (m_vertices.size() == 0)
        return{ { 0.f, 0.f }, { 0.f, 0.f } };

    const sf::Transform transform{ getTransform() };
    sf::Vector2f topLeft{ transform.transformPoint(m_vertices[0].position) };
    sf::Vector2f bottomRight{ topLeft };
    sf::Vector2f current;
    for (auto& vertex : m_vertices)
    {
        current = transform.transformPoint(vertex.position);
        if (current.x < topLeft.x)
            topLeft.x = current.x;
        else if (current.x > bottomRight.x)
            bottomRight.x = current.x;
        if (current.y < topLeft.y)
            topLeft.y = current.y;
        else if (current.y > bottomRight.y)
            bottomRight.y = current.y;
    }
    return{ topLeft, bottomRight - topLeft };
}