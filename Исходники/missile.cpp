//------------------------------------------------------------------------------
void Missile::frameMove(float dt)
{
    Projectile::frameMove(dt);


    updateTarget(dt);


    Vector cur_dir = getGlobalLinearVel();
    cur_dir.normalize();

    Vector target_dir = target_ - getPosition();
    float l = target_dir.length();
    if (equalsZero(l)) return;
    target_dir /= l;

    float alpha = acosf(vecDot(&cur_dir, &target_dir));

    if (alpha > agility_*dt )
    {
        Matrix m;
        Vector axis;
        vecCross(&axis, &target_dir, &cur_dir);
        if (!equalsZero(axis.length()))
        {
            m.loadRotationVector(agility_*dt, axis);
            target_dir = m.transformVector(cur_dir);
        } else target_dir = cur_dir;
    }
    setGlobalLinearVel(target_dir*speed_);    
}