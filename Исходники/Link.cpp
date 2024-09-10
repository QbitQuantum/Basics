void Link::update(sf::Time dt)
{
    if (sEngineRef().inputManager().keyboard().isKeyDown(imp_playerLeft->toBinding().Key))
        move(-64*dt.asSeconds(), 0);
    if (sEngineRef().inputManager().keyboard().isKeyDown(imp_playerRight->toBinding().Key))
        move(+64*dt.asSeconds(), 0);
    if (sEngineRef().inputManager().keyboard().isKeyDown(imp_playerUp->toBinding().Key))
        move(0, -64*dt.asSeconds());
    if (sEngineRef().inputManager().keyboard().isKeyDown(imp_playerDown->toBinding().Key))
        move(0, +64*dt.asSeconds());

    Player::update(dt);
    m_currentSprite->setPosition(m_pos);
    m_currentSprite->update(dt);
}