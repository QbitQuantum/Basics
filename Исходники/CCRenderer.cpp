bool CCRenderer::setup()
{
    viewportX = viewportY = viewportWidth = viewportHeight = 0.0f;
    scissorX = scissorY = scissorWidth = scissorHeight = 0.0f;

    usingOpenGL2 = true;
	renderFlags = render_all;
    if( !createContext() || !loadShaders() )
    {
        return false;
    }
    DEBUG_OPENGL();

    // All current iPhoneOS devices support BGRA via an extension.
    BGRASupport = CCTextureBase::ExtensionSupported( "GL_IMG_texture_format_BGRA8888" );

    frameBufferManager.setup();
    DEBUG_OPENGL();

    // Screen dimensions
    setupScreenSizeParams();

    return true;
}