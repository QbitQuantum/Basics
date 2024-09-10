void Rift::render(Vector3f EyePos, Vector3f EyeRot, OVR::Vector3f EyeOffset, 
                  bool use_EyeOffset, void (*draw_scene)(void)){

    // Rotate and position View Camera, using YawPitchRoll in BodyFrame coordinates.
    Matrix4f rollPitchYaw = Matrix4f::RotationY(_EyeYaw+EyeRot.y) * 
                            Matrix4f::RotationX(_EyePitch+EyeRot.x) *
                            Matrix4f::RotationZ(_EyeRoll+EyeRot.z);
    Vector3f up      = rollPitchYaw.Transform(UpVector);
    Vector3f forward = rollPitchYaw.Transform(ForwardVector);
    // Minimal head modelling.
    float headBaseToEyeHeight     = 0.15f;  // Vertical height of eye from base of head
    float headBaseToEyeProtrusion = 0.09f;  // Distance forward of eye from base of head

    Vector3f eyeCenterInHeadFrame(0.0f, headBaseToEyeHeight, -headBaseToEyeProtrusion);
    Vector3f shiftedEyePos = EyePos + rollPitchYaw.Transform(eyeCenterInHeadFrame);
    //printf("Shifted Eye Pos: %f, %f, %f\n", shiftedEyePos.x, shiftedEyePos.y, shiftedEyePos.z);
    shiftedEyePos.y -= eyeCenterInHeadFrame.y; // Bring the head back down to original height

    Matrix4f View;

    if (use_EyeOffset){
        EyePos += EyeOffset;
        View = Matrix4f::LookAtRH(EyePos, EyePos + forward, up); 
    } else {
        View = Matrix4f::LookAtRH(shiftedEyePos, shiftedEyePos + forward, up); 
    }

    const StereoEyeParams& stereo_left = _SConfig.GetEyeRenderParams(StereoEye_Left);
    const StereoEyeParams& stereo_right = _SConfig.GetEyeRenderParams(StereoEye_Right);

    // distortion shaders, if active
    // Render to first framebuffer
    glActiveTexture(0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    if (_PostProcess == PostProcess_Distortion)
        glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(0);

    switch(_SConfig.GetStereoMode())
    {
    case Stereo_None:
        render_one_eye(_SConfig.GetEyeRenderParams(StereoEye_Center), View, EyePos, draw_scene);
        break;

    case Stereo_LeftRight_Multipass:
        _which_eye = 'l';
        render_one_eye(stereo_left, View, EyePos, draw_scene);
        _which_eye = 'r';
        render_one_eye(stereo_right, View, EyePos, draw_scene);
        break;
    }
    _which_eye = 'n';
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Apply stereowarp, mapping it out to second framebuffer
    if (_PostProcess == PostProcess_Distortion){
        stereoWarp(_fbo_spare, _render_texture);
        // Draw final fbo to screen
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        // Don't use a program.  That is, use the fixed funtion pipeline.
        glUseProgram(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _render_texture_spare);
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0,0,_width,_height);
        renderFullscreenQuad();
        // But make sure we get back to normal afterwards.
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
    }

    glutSwapBuffers();  

}