void HexagonMirrorApp::draw()
{
    // clear the window
    gl::clear();

    // activate our camera
    gl::pushMatrices();
    gl::setMatrices( mCamera.getCamera() );

    // set render states
    gl::enable( GL_CULL_FACE );
    gl::enableDepthRead();
    gl::enableDepthWrite();
    gl::color( Color::white() );

    if( mVboMesh && mShaderInstanced && mBuffer )
    {
        // bind webcam image
        if( mWebcamTexture )
            mWebcamTexture.bind(0);

        // bind the shader, which will do all the hard work for us
        mShaderInstanced.bind();
        mShaderInstanced.uniform( "texture", 0 );
        mShaderInstanced.uniform( "scale", Vec2f( 1.0f / (3.0f * INSTANCES_PER_ROW), 1.0f / (3.0f * INSTANCES_PER_ROW) ) );

        // bind the buffer containing the model matrix for each instance,
        // this will allow us to pass this information as a vertex shader attribute.
        // See: initializeBuffer()
        glBindVertexArray(mVAO);

        // we do all positioning in the shader, and therefor we only need
        // a single draw call to render all instances.
        drawInstanced( mVboMesh, NUM_INSTANCES );

        // make sure our VBO is no longer bound
        mVboMesh.unbindBuffers();

        // unbind vertex array object containing our buffer
        glBindVertexArray(0);

        // unbind shader
        mShaderInstanced.unbind();

        if( mWebcamTexture )
            mWebcamTexture.unbind();
    }

    // reset render states
    gl::disableDepthWrite();
    gl::disableDepthRead();
    gl::disable( GL_CULL_FACE );

    // restore 2D drawing
    gl::popMatrices();
}