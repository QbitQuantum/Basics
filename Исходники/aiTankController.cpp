void AiTankController::stepMoveTo()
{
    if (!isAttached())
    {
        bCheckMoveTo = false;
        return;
    }
    Point2f posTank;
    float orientionTank;
    Entity &e = entity->getEntity();
    if (e.getStatus(Entity::ESI_Position, &posTank) &&
        e.getStatus(Entity::ESI_Orientation, &orientionTank))
    {
    //#ifndef NDEBUG
        iRenderQueue::getSingleton().render(moveToPos, posTank, ARGB(255, 0, 0, 0));
//#endif
        Point2f dir = moveToPos - posTank;
        float len = dir.Length();
        float len2 = (nextMoveToPos - posTank).Length();
        if (len < 10 || len > len2)
        {
            bCheckMoveTo = false;
            bForward = false;
            sendCommand(Tank::TCI_Forward, (void *)bForward);
            return;
        }
        dir.Normalize();
        if (fabs(dir ^ Point2f(cos(orientionTank), sin(orientionTank))) < 0.3f)
        {
            if (!bForward)
            {
                bForward = true;
                sendCommand(Tank::TCI_Forward, (void *)bForward);
            }
        }
        else
        {
            float lerpValue = (float)rand() / RAND_MAX;
            lerpValue *= lerpValue;
            turnTo(moveToPos);//lerp(moveToPos, nextMoveToPos, lerpValue));
            if (bForward)
            {
                bForward = false;
                sendCommand(Tank::TCI_Forward, (void *)bForward);
            }
        }
    }
    else
    {
        bCheckMoveTo = false;
    }
}