void intro_do(long t, long delta_time)
{
    char errorText[MAX_ERROR_LENGTH + 1];
    float ftime = 0.001f*(float)t;
    float fdelta_time = 0.001f * (float)(delta_time);
    GLuint textureID;

    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    // Those are key-Press indicators. I only act on 0-to-1.
    for (int i = 0; i < maxNumParameters; i++)
    {
        float destination_value = params.getParam(i, defaultParameters[i]);
        interpolatedParameters[i] = expf(-2.5f*fdelta_time) * interpolatedParameters[i] +
            (1.0f - expf(-2.5f*fdelta_time)) * destination_value;
    }
    // Update key press events.
    for (int i = 0; i < NUM_KEYS; i++)
    {
        if (params.getParam(i, 0.0) > 0.5f) keyPressed[i]++;
        else keyPressed[i] = 0;
    }

    // BPM => spike calculation
    float BPS = BPM / 60.0f;
    float jumpsPerSecond = BPS / 1.0f; // Jump on every fourth beat.
    static float phase = 0.0f;
    float jumpTime = (ftime * jumpsPerSecond) + phase;
    jumpTime -= (float)floor(jumpTime);
    if (keyPressed[41] == 1)
    {
        phase -= jumpTime;
        jumpTime = 0.0f;
        if (phase < 0.0f) phase += 1.0;
    }
    jumpTime = jumpTime * jumpTime;
    // spike is between 0.0 and 1.0 depending on the position within whatever.
    float spike = 0.5f * cosf(jumpTime * 3.1415926f * 1.5f) + 0.5f;
    // blob is growing down from 1. after keypress
    static float lastFTime = 0.f;
    blob *= (float)exp(-(float)(ftime - lastFTime) * BLOB_FADE_SPEED);
    lastFTime = ftime;

    // Set the program uniforms
    GLuint programID;
    shaderManager.getProgramID(usedProgram[usedIndex], &programID, errorText);
    glUseProgram(programID);
#if 1
    GLuint loc = glGetUniformLocation(programID, "aspectRatio");
    glUniform1f(loc, aspectRatio);
    loc = glGetUniformLocation(programID, "time");
    glUniform1f(loc, (float)(t * 0.001f));
    // For now I am just sending the spike to the shader. I might need something better...
    loc = glGetUniformLocation(programID, "spike");
    glUniform1f(loc, spike);
    loc = glGetUniformLocation(programID, "blob");
    glUniform1f(loc, blob);
    loc = glGetUniformLocation(programID, "knob1");
    glUniform1f(loc, interpolatedParameters[14]);
    loc = glGetUniformLocation(programID, "knob2");
    glUniform1f(loc, interpolatedParameters[15]);
    loc = glGetUniformLocation(programID, "knob3");
    glUniform1f(loc, interpolatedParameters[16]);
    loc = glGetUniformLocation(programID, "knob4");
    glUniform1f(loc, interpolatedParameters[17]);
    loc = glGetUniformLocation(programID, "knob5");
    glUniform1f(loc, interpolatedParameters[18]);
    loc = glGetUniformLocation(programID, "knob6");
    glUniform1f(loc, interpolatedParameters[19]);
    loc = glGetUniformLocation(programID, "knob7");
    glUniform1f(loc, interpolatedParameters[20]);
    loc = glGetUniformLocation(programID, "knob8");
    glUniform1f(loc, interpolatedParameters[21]);
    loc = glGetUniformLocation(programID, "knob9");
    glUniform1f(loc, interpolatedParameters[22]);
    loc = glGetUniformLocation(programID, "slider1");
    glUniform1f(loc, interpolatedParameters[2]);
    loc = glGetUniformLocation(programID, "slider2");
    glUniform1f(loc, interpolatedParameters[3]);
    loc = glGetUniformLocation(programID, "slider3");
    glUniform1f(loc, interpolatedParameters[4]);
    loc = glGetUniformLocation(programID, "slider4");
    glUniform1f(loc, interpolatedParameters[5]);
    loc = glGetUniformLocation(programID, "slider5");
    glUniform1f(loc, interpolatedParameters[6]);
    loc = glGetUniformLocation(programID, "slider6");
    glUniform1f(loc, interpolatedParameters[8]);
    loc = glGetUniformLocation(programID, "slider7");
    glUniform1f(loc, interpolatedParameters[9]);
    loc = glGetUniformLocation(programID, "slider8");
    glUniform1f(loc, interpolatedParameters[12]);
    loc = glGetUniformLocation(programID, "slider9");
    glUniform1f(loc, interpolatedParameters[13]);
#endif

    // Set texture identifiers
    GLint texture_location;
    texture_location = glGetUniformLocation(programID, "Noise3DTexture");
    glUniform1i(texture_location, 0);
    texture_location = glGetUniformLocation(programID, "DepthSensorTexture");
    glUniform1i(texture_location, 1);
    texture_location = glGetUniformLocation(programID, "BGTexture");
    glUniform1i(texture_location, 2);

    // render to larger offscreen texture
    glActiveTexture(GL_TEXTURE2);
    textureManager.getTextureID("hermaniak.tga", &textureID, errorText);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glActiveTexture(GL_TEXTURE1);
    //textureManager.getTextureID(TM_DEPTH_SENSOR_NAME, &textureID, errorText);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glActiveTexture(GL_TEXTURE0);
    textureManager.getTextureID(TM_NOISE3D_NAME, &textureID, errorText);
    glBindTexture(GL_TEXTURE_3D, textureID);

#if 1
    glViewport(0, 0, X_HIGHLIGHT, Y_HIGHLIGHT);
#endif

    // TODO: Here is the rendering done!
    interpolatedParameters[6] = 0.4f;

    shaderManager.getProgramID("SimpleTexture.gprg", &programID, errorText);
    glUseProgram(programID);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    //glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_DST_COLOR, GL_ZERO);

    // Texture for first pass is simply black
    textureManager.getTextureID("black.tga", &textureID, errorText);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    const int num_passes = 4;

    // TODO: Make the first 1 or 2 passes to the smaller backbuffer
    for (int pass = 0; pass < num_passes; pass++) {
        // Set small
        
        // In the first pass, use highlight
        if (pass < num_passes - 3) {
            glViewport(0, 0, X_HIGHLIGHT, Y_HIGHLIGHT);
        } else if (pass < num_passes - 1) {
            glViewport(0, 0, X_OFFSCREEN, Y_OFFSCREEN);
        } else {
            // Set the whole screen as viewport so that it is used in the last pass
            int xres = windowRect.right - windowRect.left;
            int yres = windowRect.bottom - windowRect.top;
            glViewport(0, 0, xres, yres);
        }

        float red = 1.0f;
        float green = 1.0f;
        float blue = 1.0f;
        glClearColor(red, green, blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw one iteration of the IFS
        float transformation[2][3];
        for (int i = 0; i < 20; i++) {
            transformation[0][0] = 0.5f * sinf(ftime * 0.133f + 0.3f + 1.3f * i) * sinf(ftime * 0.051f + 2.8f + 4.2f * i);
            transformation[0][1] = 0.5f * sinf(ftime * 0.051f + 2.8f + 4.2f * i) * sinf(ftime * 0.087f + 4.1f + 2.3f * i);
            transformation[0][2] = 0.6f * sinf(ftime * 0.087f + 4.1f + 2.3f * i) * sinf(ftime * 0.077f + 3.2f + 6.1f * i);
            transformation[1][0] = 0.5f * sinf(ftime * 0.077f + 3.2f + 6.1f * i) * sinf(ftime * 0.028f + 7.1f + 1.9f * i);
            transformation[1][1] = 0.5f * sinf(ftime * 0.028f + 7.1f + 1.9f * i) * sinf(ftime * 0.095f + 2.3f + 0.7f * i);
            transformation[1][2] = 0.6f * sinf(ftime * 0.095f + 2.3f + 0.7f * i) * sinf(ftime * 0.133f + 0.3f + 1.3f * i);
            DrawQuad(transformation, 1.0f);
        }

        // Copy backbuffer to texture
        if (pass < num_passes - 3) {
            textureManager.getTextureID(TM_HIGHLIGHT_NAME, &textureID, errorText);
            glBindTexture(GL_TEXTURE_2D, textureID);
            glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, X_HIGHLIGHT, Y_HIGHLIGHT);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureID);
        } else if (pass < num_passes - 1) {
            textureManager.getTextureID(TM_OFFSCREEN_NAME, &textureID, errorText);
            glBindTexture(GL_TEXTURE_2D, textureID);
            glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, X_OFFSCREEN, Y_OFFSCREEN);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureID);
        }
    }

#if 0
	// Copy backbuffer to front (so far no improvement)
	int xres = windowRect.right - windowRect.left;
	int yres = windowRect.bottom - windowRect.top;
	glViewport(0, 0, xres, yres);
    shaderManager.getProgramID("SimpleTexture.gprg", &programID, errorText);
	glUseProgram(programID);
    loc = glGetUniformLocation(programID, "time");
	glUniform1f(loc, (float)(t * 0.001f));
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_BLEND);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-1.0f, 1.0f);
	glEnd();
#endif
}