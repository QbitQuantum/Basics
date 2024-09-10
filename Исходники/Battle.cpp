AppLayer::Status Battle::tick(std::vector<sf::Event> &e, const sf::Time &t, sf::Vector2f m)
{
    //Process events
    for (unsigned i = 0; i < e.size(); i++) {
        //Keyboard events
        if (e[i].type == sf::Event::KeyPressed) {
            bool esc = controller.pressing(GameController::K_ESCAPE, e[i].key.code);

            if (esc) {
                Layer::pauseBattle();
                return AppLayer::HALT;
            }
        }
    }

    //Adjust mouse position relative to map (camera)
    sf::Vector2f hsize = sf::Vector2f(camera.getSize().x/2, camera.getSize().y/2);
    m += camera.getCenter() - hsize;

    //Direct level transition
    if (m_transitioning) {
        m_transitionDuration -= t.asSeconds();
        if (m_transitionDuration <= 0) {
            endLevelTransition();
        }
        else {
            float alpha = 1.f - m_transitionDuration / 1.5f; 
            alpha *= alpha*10*alpha;
            gAgent->setTransition(alpha);
            hAgent->setTransition(alpha);
        }
    }

    //Progress components
    mAgent->updateState(t, m);
    gAgent->updateState(mAgent->getBattleState());
    hAgent->updateState(mAgent->getBattleState());
    
    //Update camera
    sf::Vector2f map = mAgent->getBattleState().map;
    sf::Vector2f pos = mAgent->getBattleState().player->getPos();
    if (pos.x < hsize.x) pos.x = hsize.x;
    else if (pos.x > map.x - hsize.x) pos.x = map.x - hsize.x;
    if (pos.y < hsize.y) pos.y = hsize.y;
    else if (pos.y > map.y - hsize.y) pos.y = map.y - hsize.y;
    camera.setCenter(pos);

    //Check for end conditions
    if (mAgent->isPlayerDead()) {
        Layer::back();
    }
    else if (!m_scoring && mAgent->isLevelDone()) {
        m_scoring = true;
        mAgent->saveLevelStats();
        mAgent->clearEnemyProjectiles();
        Layer::goToScoreScreen();
    }
    
    return AppLayer::HALT;
}