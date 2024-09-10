void rainDrop::update(CameraClass *camera)
{
    if (!alive)
    {
        triggerTick += 15;
    
        if (triggerTick > triggerDelay)
        {
            alive = true;
            triggerTick = 0;
        }
    }

    else
    {    
        y -= 0.45;

        if (y < -5)
        {
           y = 10;
           x = initial_x + XMVectorGetX(camera -> getPos());
           z = initial_z + XMVectorGetZ(camera -> getPos());
           alive = false;
        }
    }
}