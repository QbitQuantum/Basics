MoveAction::MoveAction(Ship *Source, Ship* Target)
    : source(Source), target(Target)
{
    Coordinates tc = target->getPosition();
    float dist = tc.distance(source->getPosition());

    if (dist > source->getBaseStats().range)
    {
        float direction = atan2(source->getY() - target->getY(), source->getX() - target->getX());
        dist -= (source->getBaseStats().range-30);
        coord.x = source->getX() - dist * cos(direction);
        coord.y = source->getY() - dist * sin(direction);
    }
    else
    {
        coord = source->getPosition();
    }

//    printf("Move To: %lf, %lf\n", coord.x, coord.y);
}