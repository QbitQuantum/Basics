Vec2 SeaFireFlyMove::middleMove(Sprite* seaFirefly, SeaFireFly* targetObject)
{
    Vec2 targetPos = targetObject->getPosition();
    Sprite* character = seaFirefly;

    Vec2 myPos = character->getPosition();

    if (targetPos == myPos)return Vec2();
    if (targetObject->getState() != FOLLOW)return Vec2();

    float distance = 0;
    float dx = targetPos.x - character->getPosition().x;
    float dy = targetPos.y - character->getPosition().y;
    Vec2 change = Vec2(dx, dy);
    change.normalize();
    change *= 5;

    return (change);
}