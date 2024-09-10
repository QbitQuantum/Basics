bool TalkingSprite::intersects(sf::FloatRect rect) const {
    for (auto && it: collisionBoxList) {
        if (rect.intersects(it)) {
            return true;
        }
    }
    return false;
}