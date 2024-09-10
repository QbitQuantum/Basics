//---------------------------------------------------------
void FSMAIControl::UpdatePerceptions(float dt)
{
    if(m_willCollide)
        m_safetyRadius = 30.0f;
    else
        m_safetyRadius = 15.0f;

    //store closest asteroid and powerup
    m_nearestAsteroid = Game.GetClosestGameObj(m_ship,GameObj::OBJ_ASTEROID);
    m_nearestPowerup  = Game.GetClosestGameObj(m_ship,GameObj::OBJ_POWERUP);

    //asteroid collision determination
    m_willCollide = false;
    if(m_nearestAsteroid)
    {
        float speed = m_ship->m_velocity.Length();
        m_nearestAsteroidDist = m_nearestAsteroid->m_position.Distance(m_ship->m_position);
        Point3f normDelta = m_nearestAsteroid->m_position - m_ship->m_position;
        normDelta.Normalize();
        float astSpeed = m_nearestAsteroid->m_velocity.Length();
        float shpSpeedAdj = DOT(m_ship->UnitVectorVelocity(),normDelta)*speed;
        float astSpeedAdj = DOT(m_nearestAsteroid->UnitVectorVelocity(),-normDelta)*astSpeed;
        speed = shpSpeedAdj+astSpeedAdj;

//        if(speed > astSpeed)
//            dotVel  = DOT(m_ship->UnitVectorVelocity(),normDelta);
//        else
//        {
//            speed = astSpeed;
//            dotVel = DOT(m_nearestAsteroid->UnitVectorVelocity(),-normDelta);
//        }
        float spdAdj = LERP(speed/m_maxSpeed,0.0f,90.0f);
        float adjSafetyRadius = m_safetyRadius+spdAdj+m_nearestAsteroid->m_size;

        //if you're too close, and I'm heading somewhat towards you,
        //flag a collision
        if(m_nearestAsteroidDist <= adjSafetyRadius && speed > 0)
            m_willCollide = true;
    }

    //powerup near determination
    m_powerupNear = false;
    if(m_nearestPowerup)
    {
        m_nearestPowerupDist = m_nearestPowerup->m_position.Distance(m_ship->m_position);
        if(m_nearestPowerupDist <= POWERUP_SCAN_DIST)
        {
            m_powerupNear     = true;
        }
    }

}