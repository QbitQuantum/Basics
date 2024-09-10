sf::Vector2f QuantumField::friction(const PointMass& caller) const
{
    if (fp::not_equal(length_squared(caller.velocity), 0.f))
    {
        return unit(caller.velocity) * (-1.f) * 10.f;
    }
    else
    {
        return {0.f, 0.f};
    }
}