Matrix3 plStaticEnvLayer::IGetViewTM( int i )
{
    Matrix3 m;
    m.IdentityMatrix();
    switch( i ) 
    {
        case kTopFace:
            m.RotateX( -M_PI );   
            break;
        case kBottomFace:
            break;
        case kLeftFace:
            m.RotateX( -.5f * M_PI ); 
            m.RotateY( -.5f * M_PI );
            break;
        case kRightFace:
            m.RotateX( -.5f * M_PI ); 
            m.RotateY( +.5f * M_PI );
            break;
        case kFrontFace:
            m.RotateX( -.5f * M_PI ); 
            m.RotateY( M_PI );
            break;
        case kBackFace:
            m.RotateX( -.5f * M_PI ); 
            break;
    }
    return m;
}