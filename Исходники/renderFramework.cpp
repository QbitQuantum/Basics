static void display()
{
    const Vector3f eyePosition(0, 0, 13);
    const Vector3f eyeCenter(0,0,0);
    const Vector3f eyeUp(0,1,0);
    const Vector3f lightPosition(5 * sin(lightAngle), 1.5, 5 * cos(lightAngle));
    Camera camera(eyePosition, eyeCenter, eyeUp);
    transform.SetCamera(camera);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cgGLBindProgram(programVertex);
    Log("binding vertex program");

    cgGLEnableProfile(profileVertex);
    Log("enabling vertex profile");

    cgGLBindProgram(programFragment);
    Log("binding fragment program");

    cgGLEnableProfile(profileFragment);
    Log("enabling fragment profile");

    setBrassMaterial();
    transform.SetTranslate(2, 0, 0);
    transform.SetArbitraryRotation(20, 1, 1, 1);
    Matrix4f modelMatrix;
    transform.GetModelMatrix(modelMatrix);
    Matrix4f invModelMatrix = modelMatrix.Invert();
    Vector4f objSpaceEyePosition = invModelMatrix.Mul(eyePosition);
    Vector4f objSpaceLightPosition = invModelMatrix.Mul(lightPosition);
    Matrix4f modelViewProjMatix;
    transform.GetMVPMatrix(modelViewProjMatix);
    CgSetParam(paramVertexmodelViewProj, modelViewProjMatix);

    //CgSetParam(paramFragmentEyePosition, objSpaceEyePosition);
    CgSetParam(paramFragmentLightPosition, objSpaceLightPosition);

    CgSetParam(paramVertexLightPosition, objSpaceLightPosition);
    CgSetParam(paramVertexEyePosition, objSpaceEyePosition);

    cgUpdateProgramParameters(programVertex);
    cgUpdateProgramParameters(programFragment);
    glutSolidSphere(2.0, 10, 10);

    cgGLDisableProfile(profileVertex);
    Log("disabling vertex profile");

    cgGLDisableProfile(profileFragment);
    Log("disabling fragment profile");
    glutSwapBuffers();
}