void Exercise20::paintGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    QGLShaderProgram* currentProg;
    if (m_shadingMode == Toon_Shading)
    {
        currentProg = m_prog_toon;
    }
    else
    {
        currentProg = m_prog_phong;
    }

    currentProg->bind();

    setupLightUniforms(currentProg);
    setupMaterialUniforms(currentProg);

    glLoadMatrixf(m_view.data());

    glPushMatrix();

    glRotatef(static_cast<float>(m_frame % (4 * 360)) * 0.25f, 0.f, 1.f, 0.f);
    glScalef(1.f, 1.f, 1.f);

    draw();

    glPopMatrix();
    currentProg->release();
}