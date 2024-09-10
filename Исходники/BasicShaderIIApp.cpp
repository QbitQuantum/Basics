void BasicShaderIIApp::update()
{
    mCam.lookAt( mEye, mTarget, Vec3f::yAxis() );

    if(mLightDir.length() != 1.0f)
        mLightDir.normalize();
}