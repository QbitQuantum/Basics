// set the rotation of the 3D viewer
void  Viewer3dParam::SetPose( Quaternion q, Vec3f t )
{

    Rotation( q.Conjugate() );
    
    Translation( t );

}