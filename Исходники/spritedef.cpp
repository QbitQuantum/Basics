static Action::SpriteDirection directionByName(const QStringRef &name)
{
    if (name.length() == 0 || name == "default")
        return Action::DIRECTION_DEFAULT;
    else if (name == "up")
        return Action::DIRECTION_UP;
    else if (name == "down")
        return Action::DIRECTION_DOWN;
    else if (name == "left")
        return Action::DIRECTION_LEFT;
    else if (name == "right")
        return Action::DIRECTION_RIGHT;
    else
        return Action::DIRECTION_INVALID;
}