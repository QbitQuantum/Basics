static void drawStuff(const ShaderState& curSS, bool picking) {
  // build & send proj. matrix to vshader
  const Matrix4 projmat = makeProjectionMatrix();
  sendProjectionMatrix(curSS, projmat);

  const RigTForm eyeRbt = getPathAccumRbt(g_world, g_currentCameraNode);
  const RigTForm invEyeRbt = inv(eyeRbt);

  if (!picking) {
    const Cvec3 eyeLight1 = Cvec3(invEyeRbt * Cvec4(g_light1, 1));
    const Cvec3 eyeLight2 = Cvec3(invEyeRbt * Cvec4(g_light2, 1));
    safe_glUniform3f(curSS.h_uLight, eyeLight1[0], eyeLight1[1], eyeLight1[2]);
    safe_glUniform3f(curSS.h_uLight2, eyeLight2[0], eyeLight2[1], eyeLight2[2]);

    Drawer drawer(invEyeRbt, curSS);
    g_world->accept(drawer);

    if (g_displayArcball && shouldUseArcball())
      drawArcBall(curSS);
  }
  else {
    // Picker picker(invEyeRbt, curSS);
    // g_world->accept(picker);
    // glFlush();
    // g_currentPickedRbtNode = picker.getRbtNodeAtXY(g_mouseClickX, g_mouseClickY);
    // if (g_currentPickedRbtNode == g_groundNode)
    //  g_currentPickedRbtNode = shared_ptr<SgRbtNode>(); // set to NULL
 
    // g_particleSystem->setFixedParticle(g_currentPickedRbtNode->getParticleId());

    // cout << (g_currentPickedRbtNode ? "Part picked" : "No part picked") << endl;
  }
}