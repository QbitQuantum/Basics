//----------------------------------------------------------------------------//
void OpenGLGLXPBTextureTarget::initialisePBuffer()
{
    int creation_attrs[] =
    {
        GLX_PBUFFER_WIDTH, d_area.getWidth(),
        GLX_PBUFFER_HEIGHT, d_area.getHeight(),
        GLX_LARGEST_PBUFFER, True,
        GLX_PRESERVED_CONTENTS, True,
        None
    };

    // release any existing pbuffer
    if (d_pbuffer)
        glXDestroyPbuffer(d_dpy, d_pbuffer);

    d_pbuffer = glXCreatePbuffer(d_dpy, d_fbconfig, creation_attrs);

    if (!d_pbuffer)
        CEGUI_THROW(RendererException(
            "pbuffer creation error:  glXCreatePbuffer() failed"));

    // get the real size of the buffer that was created
    GLuint actual_width, actual_height;
    glXQueryDrawable(d_dpy, d_pbuffer, GLX_WIDTH, &actual_width);
    glXQueryDrawable(d_dpy, d_pbuffer, GLX_HEIGHT, &actual_height);
    d_area.setSize(Sizef(actual_width, actual_height));

    // ensure CEGUI::Texture is wrapping real GL texture and has correct size
    d_CEGUITexture->setOpenGLTexture(d_texture, d_area.getSize());
}