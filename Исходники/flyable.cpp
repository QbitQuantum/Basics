/** Updates this flyable. It calls Moveable::update. If this function returns
 *  true, the flyable will be deleted by the projectile manager.
 *  \param dt Time step size.
 *  \returns True if this object can be deleted.
 */
bool Flyable::updateAndDelete(int ticks)
{
    if (m_undo_creation)
        return false;

    if (hasAnimation())
    {
        if (!RewindManager::get()->isRewinding())
        {
            m_animation->update(ticks);
            Moveable::update(ticks);
        }
        return false;
    }   // if animation

    m_ticks_since_thrown += ticks;
    if(m_max_lifespan > -1 && m_ticks_since_thrown > m_max_lifespan)
        hit(NULL);

    if(m_has_hit_something) return true;

    //Vec3 xyz=getBody()->getWorldTransform().getOrigin();
    const Vec3 &xyz=getXYZ();
    // Check if the flyable is outside of the track. If so, explode it.
    const Vec3 *min, *max;
    Track::getCurrentTrack()->getAABB(&min, &max);

    // I have seen that the bullet AABB can be slightly different from the
    // one computed here - I assume due to minor floating point errors
    // (e.g. 308.25842 instead of 308.25845). To avoid a crash with a bullet
    // assertion (see bug 3058932) I add an epsilon here - but admittedly
    // that does not really explain the bullet crash, since bullet tests
    // against its own AABB, and should therefore not cause the assertion.
    // But since we couldn't reproduce the problem, and the epsilon used
    // here does not hurt, I'll leave it in.
    float eps = 0.1f;
    assert(!std::isnan(xyz.getX()));
    assert(!std::isnan(xyz.getY()));
    assert(!std::isnan(xyz.getZ()));
    if(xyz[0]<(*min)[0]+eps || xyz[2]<(*min)[2]+eps || xyz[1]<(*min)[1]+eps ||
       xyz[0]>(*max)[0]-eps || xyz[2]>(*max)[2]-eps || xyz[1]>(*max)[1]-eps   )
    {
        hit(NULL);    // flyable out of track boundary
        return true;
    }

    if (m_do_terrain_info)
    {
        Vec3 towards = getBody()->getGravity();
        towards.normalize();
        // Add the position offset so that the flyable can adjust its position
        // (usually to do the raycast from a slightly higher position to avoid
        // problems finding the terrain in steep uphill sections).
        // Towards is a unit vector. so we can multiply -towards to offset the
        // position by one unit.
        TerrainInfo::update(xyz + m_position_offset*(-towards), towards);

        // Make flyable anti-gravity when the it's projected on such surface
        const Material* m = TerrainInfo::getMaterial();
        if (m && m->hasGravity())
        {
            getBody()->setGravity(TerrainInfo::getNormal() * -70.0f);
        }
        else
        {
            getBody()->setGravity(Vec3(0, 1, 0) * -70.0f);
        }
    }

    if(m_adjust_up_velocity)
    {
        float hat = (xyz - getHitPoint()).length();

        // Use the Height Above Terrain to set the Z velocity.
        // HAT is clamped by min/max height. This might be somewhat
        // unphysical, but feels right in the game.

        float delta = m_average_height - std::max(std::min(hat, m_max_height),
                                                  m_min_height);
        Vec3 v = getVelocity();
        assert(!std::isnan(v.getX()));
        assert(!std::isnan(v.getX()));
        assert(!std::isnan(v.getX()));
        float heading = atan2f(v.getX(), v.getZ());
        assert(!std::isnan(heading));
        float pitch   = getTerrainPitch(heading);
        float vel_up = m_force_updown*(delta);
        if (hat < m_max_height) // take into account pitch of surface
            vel_up += v.length_2d()*tanf(pitch);
        assert(!std::isnan(vel_up));
        v.setY(vel_up);
        setVelocity(v);
    }   // if m_adjust_up_velocity

    Moveable::update(ticks);

    return false;
}   // updateAndDelete