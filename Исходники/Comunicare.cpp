std::string Comunicare :: interactTastatura(sf::RenderWindow &fereastra, sf::Event &ev)
{
    static sf::Clock timpActiune;
    float timpRamas = timpActiune.getElapsedTime().asSeconds();
    if(ev.type == sf::Event::TextEntered)
        text_dl_tastatura += (char)ev.text.unicode;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        if(timpRamas > 0.1)
        {
            timpActiune.restart();
            text_dl_tastatura += '\n';
        }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !text_dl_tastatura.empty())
        text_dl_tastatura.erase(text_dl_tastatura.size()-1,1);
}