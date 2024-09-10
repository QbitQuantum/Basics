void rayMarcherApp::setup()
{
    CameraPersp cam;
    mStartEyePoint = Vec3f( 15, 21, 27.5 ) * 0.65f;
    cam.lookAt( mStartEyePoint, Vec3f::zero(), Vec3f::yAxis() );
    cam.setCenterOfInterest( mStartEyePoint.distance( Vec3f::zero() ) );
    mMayaCam.setCurrentCam( cam );
}