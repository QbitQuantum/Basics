void CameraSettings::spinModel( const float x, const float y, const float z )
{
    if( x == 0.f && y == 0.f && z == 0.f )
        return;

    Matrix4f matInverse;
    cameraRotation_.inverse( matInverse );
    Vector4f shift = matInverse * Vector4f( x, y, z, 1 );
    modelRotation_.pre_rotate_x( shift.x( ));
    modelRotation_.pre_rotate_y( shift.y( ));
    modelRotation_.pre_rotate_z( shift.z( ));

    setDirty( DIRTY_ALL );
}