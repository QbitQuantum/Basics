//----------------------------------------------------------------------------//
OpenGLViewportTarget::OpenGLViewportTarget(OpenGLRendererBase& owner) :
    OpenGLRenderTarget<>(owner)
{
    // viewport area defaults to whatever the current OpenGL viewport is set to
    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);

    Rectf init_area(Vector2f(static_cast<float>(vp[0]), static_cast<float>(vp[1])),
                        Sizef(static_cast<float>(vp[2]), static_cast<float>(vp[3])));

    setArea(init_area);
}