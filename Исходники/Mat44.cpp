// MakeLookAt
//------------------------------------------------------------------------------
void Mat44::MakeLookAt( const Vec3 & pos, const Vec3 & lookAt, const Vec3 & upVector )
{
    // generate the forward vector
    Vec3 forward( pos - lookAt );
    forward.Normalise();

    Vec3 right = upVector.Cross( forward );
    right.Normalise();

    Vec3 up = forward.Cross( right );
    up.Normalise();

    col0 = Vec4( right.x, up.x, forward.x, 0.0f );
    col1 = Vec4( right.y, up.y, forward.y, 0.0f ),
    col2 = Vec4( right.z, up.z, forward.z, 0.0f ),
    col3 = Vec4( -right.Dot( pos ), -up.Dot( pos ), -forward.Dot( pos ), 1.0f );
}