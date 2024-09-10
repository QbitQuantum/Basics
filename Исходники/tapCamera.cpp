Vec3 TapCamera::PointOnSphere( Vec2& point )
{
    Vec3 ball_mouse;
    float mag;
    Vec2 vec = (point - vec_ball_center_) / ball_radius_;
    mag = vec.Dot( vec );
    if( mag > 1.f )
    {
        float scale = 1.f / sqrtf( mag );
        vec *= scale;
        ball_mouse = Vec3( vec, 0.f );
    }
    else
    {
        ball_mouse = Vec3( vec, sqrtf( 1.f - mag ) );
    }
    return ball_mouse;
}