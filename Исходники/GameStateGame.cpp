void GameStateGame::Update(const sf::Time& time)
{
    SharedContext* context = m_stateMgr->GetContext();
    EntityBase   * player  = context->entityManager->Find("Player");
    if (!player)
    {
        std::cout << "Respawning player..." << std::endl;
        context->entityManager->Add(EntityType::Player, "Player");
        player = context->entityManager->Find("Player");
        player->SetPosition(m_gameMap->GetPlayerStart());
        std::cout << "Player respawned..." << std::endl;
    }
    else
    {
        m_view.setCenter(player->GetPosition());
        context->window->GetRenderWindow()->setView(m_view);
    }

    sf::FloatRect viewSpace = context->window->GetViewSpace();

    if (viewSpace.left <= 0)
    {
        m_view.setCenter(viewSpace.width / 2.0f, m_view.getCenter().y);
        context->window->GetRenderWindow()->setView(m_view);
    }
    else if (viewSpace.left + viewSpace.width > (m_gameMap->GetMapSize().x) * TILE_SIZE)
    {
        m_view.setCenter(((m_gameMap->GetMapSize().x) * TILE_SIZE) - (viewSpace.width / 2.0f),
                         m_view.getCenter().y);
        context->window->GetRenderWindow()->setView(m_view);
    }

    if (viewSpace.top <= 0)
    {
        m_view.setCenter(m_view.getCenter().x, viewSpace.height / 2.0f);
        context->window->GetRenderWindow()->setView(m_view);
    }
    else if (viewSpace.top + viewSpace.height >
             (m_gameMap->GetMapSize().y) * TILE_SIZE)
    {
        m_view.setCenter(m_view.getCenter().x,
                         ((m_gameMap->GetMapSize().y) *
                          TILE_SIZE) - (viewSpace.height / 2.0f));
        context->window->GetRenderWindow()->setView(m_view);
    }

    m_gameMap->Update(time.asSeconds());
    m_stateMgr->GetContext()->entityManager->Update(time.asSeconds());
}