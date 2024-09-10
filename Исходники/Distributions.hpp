NDistribution<sf::Time> uniform(sf::Time min, sf::Time max)
{
    assert(min <= max);

    const float floatMin = min.asSeconds();
    const float floatMax = max.asSeconds();

    return [=] () -> sf::Time
    {
        return sf::seconds(NMath::random(floatMin, floatMax));
    };
}