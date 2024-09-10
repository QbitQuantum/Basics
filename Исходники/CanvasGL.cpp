void Canvas::Impl::endTranslucent(float alpha)
{
    glFlush();

    assert(!translucents.empty());
    GLuint tex = translucents.back();
    translucents.pop_back();

    GLuint next = translucents.empty() ? texture : translucents.back();
    if (GLEW_ARB_framebuffer_object)
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, next, 0);
    else
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, next, 0);

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);
    alphaBlend(width, height, alpha, tex);
    glPopMatrix();

    glDeleteTextures(1, &tex);
}