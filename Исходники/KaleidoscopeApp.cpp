void KaleidoscopeApp::draw()
{
    gl::clear();

    gl::setViewport( getWindowBounds() );
    gl::setMatricesWindow( getWindowSize() );

    if ( mShader )
    {
        mShader.bind();
        mShader.uniform( "center", mCenter );
        mShader.uniform( "numReflectionLines", mNumReflectionLines );
        mShader.uniform( "rotation", mRotation );
        mShader.uniform( "txt", 0 );
    }

    if ( mTexture )
        gl::draw( mTexture, getWindowBounds() );

    if ( mShader )
        mShader.unbind();

    mParams.draw();
}