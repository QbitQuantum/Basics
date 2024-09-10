void Editor::draw(const Dot &dot)
{
    // Cross
    sf::RectangleShape horizontal(sf::Vector2f(7, 3)), vertical(sf::Vector2f(3, 7));
    horizontal.setPosition(dot.pos().x-3, dot.pos().y-1);
    vertical.setPosition(dot.pos().x-1, dot.pos().y-3);
    // Text
    sf::Text text(std::to_string(dot.number()), _font);
    text.setCharacterSize(12);
    text.setPosition(dot.pos().x - 5, dot.pos().y - 18);
    // Colors
    horizontal.setFillColor(sf::Color::Red);
    vertical.setFillColor(sf::Color::Red);
    text.setColor(sf::Color::Black);
    // Draw
    _window.draw(horizontal);
    _window.draw(vertical);
    _window.draw(text);
}