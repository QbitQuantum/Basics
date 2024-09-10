void pattern_render(struct pattern * pattern, GLuint input_tex) {
    GLenum e;

    glLoadIdentity();
    glViewport(0, 0, config.pattern.master_width, config.pattern.master_height);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, pattern->fb);

    pattern->intensity_integral = fmod(pattern->intensity_integral + pattern->intensity / config.ui.fps, MAX_INTEGRAL);

    for (int i = pattern->n_shaders - 1; i >= 0; i--) {
        glUseProgramObjectARB(pattern->shader[i]);

        // Don't worry about this part.
        for(int j = 0; j < pattern->n_shaders; j++) {
            // Or, worry about it, but don't think about it.
            glActiveTexture(GL_TEXTURE1 + j);
            glBindTexture(GL_TEXTURE_2D, pattern->tex[(pattern->flip + j + (i < j)) % (pattern->n_shaders + 1)]);
        }
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D,
                                  pattern->tex[(pattern->flip + i + 1) % (pattern->n_shaders + 1)], 0);

        if((e = glGetError()) != GL_NO_ERROR) FAIL("OpenGL error: %s\n", gluErrorString(e));

        GLint loc;
        loc = glGetUniformLocationARB(pattern->shader[i], "iTime");
        glUniform1fARB(loc, time_master.beat_frac + time_master.beat_index);
        loc = glGetUniformLocationARB(pattern->shader[i], "iAudioHi");
        glUniform1fARB(loc, audio_hi);
        loc = glGetUniformLocationARB(pattern->shader[i], "iAudioMid");
        glUniform1fARB(loc, audio_mid);
        loc = glGetUniformLocationARB(pattern->shader[i], "iAudioLow");
        glUniform1fARB(loc, audio_low);
        loc = glGetUniformLocationARB(pattern->shader[i], "iAudioLevel");
        glUniform1fARB(loc, audio_level);
        loc = glGetUniformLocationARB(pattern->shader[i], "iResolution");
        glUniform2fARB(loc, config.pattern.master_width, config.pattern.master_height);
        loc = glGetUniformLocationARB(pattern->shader[i], "iIntensity");
        glUniform1fARB(loc, pattern->intensity);
        loc = glGetUniformLocationARB(pattern->shader[i], "iIntensityIntegral");
        glUniform1fARB(loc, pattern->intensity_integral);
        loc = glGetUniformLocationARB(pattern->shader[i], "iFPS");
        glUniform1fARB(loc, config.ui.fps);
        loc = glGetUniformLocationARB(pattern->shader[i], "iFrame");
        glUniform1iARB(loc, 0);
        loc = glGetUniformLocationARB(pattern->shader[i], "iChannel");
        glUniform1ivARB(loc, pattern->n_shaders, pattern->uni_tex);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, input_tex);

        if((e = glGetError()) != GL_NO_ERROR) FAIL("OpenGL error: %s\n", gluErrorString(e));

        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_QUADS);
        glVertex2d(-1, -1);
        glVertex2d(-1, 1);
        glVertex2d(1, 1);
        glVertex2d(1, -1);
        glEnd();

        if((e = glGetError()) != GL_NO_ERROR) FAIL("OpenGL error: %s\n", gluErrorString(e));
    }
    pattern->flip = (pattern->flip + 1) % (pattern->n_shaders + 1);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

    if((e = glGetError()) != GL_NO_ERROR) FAIL("OpenGL error: %s\n", gluErrorString(e));
    pattern->tex_output = pattern->tex[pattern->flip];
}