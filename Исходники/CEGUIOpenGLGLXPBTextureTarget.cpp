//----------------------------------------------------------------------------//
OpenGLGLXPBTextureTarget::OpenGLGLXPBTextureTarget(OpenGLRenderer& owner) :
    OpenGLTextureTarget(owner),
    d_pbuffer(0)
{
    if (!GLXEW_VERSION_1_3)
        throw InvalidRequestException("System does not support GLX >= 1.3 "
            "required by CEGUI pbuffer usage under GLX");

    d_dpy = glXGetCurrentDisplay();

    selectFBConfig();
    createContext();
    initialiseTexture();

    // set default size (and cause initialisation of the pbuffer)
    declareRenderSize(Size(DEFAULT_SIZE, DEFAULT_SIZE));

    // set some states as a one-time thing (because we use a separate context)
    enablePBuffer();

    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_SECONDARY_COLOR_ARRAY);
    glDisableClientState(GL_INDEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_FOG_COORDINATE_ARRAY);
    glDisableClientState(GL_EDGE_FLAG_ARRAY);
    glClearColor(0,0,0,0);

    disablePBuffer();
}