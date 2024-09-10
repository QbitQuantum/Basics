/**
 the draw method displays the last filled buffer
 **/
void millionParticlesApp::draw()
{
    gl::setMatricesWindow( getWindowSize() );
    gl::setViewport( getWindowBounds() );

    gl::clear( ColorA( 0.0f, 0.0f, 0.0f, 1.0f ) );

    gl::enableAlphaBlending();
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    mFbo[mBufferIn].bindTexture(0,0);
    mFbo[mBufferIn].bindTexture(1,1);
    mFbo[mBufferIn].bindTexture(2,2);

    mSpriteTex.bind(3);

    //Bewegungsshader
    mPosShader.bind();
    mPosShader.uniform("posTex",0);
    mPosShader.uniform("velTex",1);
    mPosShader.uniform("infTex",2);
    mPosShader.uniform("spriteTex",3);

    mPosShader.uniform("scale",(float)PARTICLES);

    gl::color(ColorA(1.0f,1.0f,1.0f,1.0f));
    //glTranslatef(Vec3f(getWindowWidth() / 4  - PARTICLES,0.0f,0.0f));
    gl::pushMatrices();

    glScalef(getWindowHeight() / (float)PARTICLES , getWindowHeight() / (float)PARTICLES ,1.0f);

    // draw particles
    gl::draw( mVbo );

    gl::popMatrices();

    mPosShader.unbind();

    mSpriteTex.unbind();

    mFbo[mBufferIn].unbindTexture();

    //    writeImage( "/Users/hacku/Desktop/img/1m/" + toString(getElapsedFrames()) + ".tif",   copyWindowSurface() );

    //	gl::color(Color(1,1,1));
    //	gl::setMatricesWindow( getWindowSize() );

    //drawText();

    gl::disableAlphaBlending();

}