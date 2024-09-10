cocos2d::Quaternion PUCircleEmitter::getRotationTo( const Vec3 &src, const Vec3& dest, const Vec3& fallbackAxis /*= Vec3::ZERO*/ ) const
{
    // Based on Stan Melax's article in Game Programming Gems
    Quaternion q;
    // Copy, since cannot modify local
    Vec3 v0 = src;
    Vec3 v1 = dest;
    v0.normalize();
    v1.normalize();

    float d = v0.dot(v1);
    // If dot == 1, vectors are the same
    if (d >= 1.0f)
    {
        return Quaternion();
    }
    if (d < (1e-6f - 1.0f))
    {
        if (fallbackAxis != Vec3::ZERO)
        {
            // rotate 180 degrees about the fallback axis
            q.set(fallbackAxis, (float)M_PI);
            //q.FromAngleAxis(Radian(Math::PI), fallbackAxis);
        }
        else
        {
            // Generate an axis
            Vec3 axis/* = Vec3::UNIT_X.crossProduct(*this)*/;
            Vec3::cross(Vec3::UNIT_X, src, &axis);
            if (axis.lengthSquared() < (1e-06 * 1e-06)) // pick another if colinear
                //axis = Vec3::UNIT_Y.crossProduct(*this);
                Vec3::cross(Vec3::UNIT_Y, src, &axis);
            axis.normalize();

            //q.FromAngleAxis(Radian(Math::PI), axis);
            q.set(axis, (float)M_PI);
        }
    }
    else
    {
        /*float s = Math::Sqrt( (1+d)*2 );*/
        float s = sqrtf( (1+d)*2 );
        float invs = 1 / s;

        Vec3 c /*= v0.crossProduct(v1)*/;
        Vec3::cross(v0, v1, &c);

        q.x = c.x * invs;
        q.y = c.y * invs;
        q.z = c.z * invs;
        q.w = s * 0.5f;
        q.normalize();
    }
    return q;
}