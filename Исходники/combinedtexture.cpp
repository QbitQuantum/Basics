void CombinedTexture::create()
{
    if (m_framebuffer)
        delete m_framebuffer;

    QOpenGLFramebufferObjectFormat format;
    format.setMipmap(true);

    m_framebuffer = new QOpenGLFramebufferObject(m_width, m_height, format);
    m_framebuffer->bind();

    glViewport(0, 0, m_width, m_height);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);

    for (int i = 0; i < m_textures.size(); i++) {
        Texture *texture = m_textures.at(i).first;
        float *position = m_textures.at(i).second;

        texture->bind();

        glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(position[0], position[1], 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(position[2], position[1], 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(position[2], position[3], 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(position[0], position[3], 0.0f);

        glEnd();
    }

    m_framebuffer->release();

    glBindTexture(GL_TEXTURE_2D, m_framebuffer->texture());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QOpenGLFunctions gl(QOpenGLContext::currentContext());
    gl.initializeOpenGLFunctions();
    gl.glGenerateMipmap(GL_TEXTURE_2D);

    m_created = true;
}