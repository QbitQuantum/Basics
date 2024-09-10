void GameInput::move(Display *display, APlayer *player, Map &map, const gdl::Clock &clock) {
    glm::vec3 translation(0, 0, 0);

    if (this->turnLeft()) {
        translation = glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * 3.0f;
    } else if (this->turnRight()) {
        translation = glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * 3.0f;
    } else if (this->turnUp()) {
        translation = glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * 3.0f;
    } else if (this->turnDown()) {
        translation = glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * 3.0f;
    }

    display->setTranslation(translation);
    player->translate(translation);

    glm::vec3 pos(-player->getPosition().x, player->getPosition().y, -player->getPosition().z);

    if (map.canMoveAt(pos)) {
        display->setTranslation(-translation);
        player->translate(-translation);
    }
}