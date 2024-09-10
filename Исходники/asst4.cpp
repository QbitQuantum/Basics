static void drawStuff(const ShaderState& curSS, bool picking) {

  setAFrame();

  // build & send proj. matrix to vshader
  const Matrix4 projmat = makeProjectionMatrix();


  sendProjectionMatrix(curSS, projmat);

  const RigTForm eyeRbt = getPathAccumRbt(g_world, g_currentView);
  
  const RigTForm invEyeRbt = inv(eyeRbt);



  const Cvec3 eyeLight1 = Cvec3(invEyeRbt * Cvec4(g_light1, 1)); // g_light1 position in eye coordinates
  const Cvec3 eyeLight2 = Cvec3(invEyeRbt * Cvec4(g_light2, 1)); // g_light2 position in eye coordinates
  safe_glUniform3f(curSS.h_uLight, eyeLight1[0], eyeLight1[1], eyeLight1[2]);
  safe_glUniform3f(curSS.h_uLight2, eyeLight2[0], eyeLight2[1], eyeLight2[2]);


  if (!picking) {
    Drawer drawer(invEyeRbt, curSS);
    g_world->accept(drawer);

    RigTForm sphereTarget;
    if (g_currentPickedRbtNode == g_skyNode) {
      if (g_currentSkyView == 0) {
        sphereTarget = inv(RigTForm());
      } else {
        sphereTarget = eyeRbt;
      }
    } else {
      sphereTarget = getPathAccumRbt(g_world, g_currentPickedRbtNode);
    }

    if (!g_mouseMClickButton && !(g_mouseLClickButton && g_mouseRClickButton) && useArcball()) {
      g_arcballScale = getScreenToEyeScale(
        (inv(eyeRbt) * sphereTarget).getTranslation()[2],
        g_frustFovY,
        g_windowHeight
      );
    }


   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    const Matrix4 scale = Matrix4::makeScale(g_arcballScale * g_arcballScreenRadius);
    Matrix4 MVM = rigTFormToMatrix(invEyeRbt * sphereTarget) * scale;
    Matrix4 NMVM = normalMatrix(MVM);
    sendModelViewNormalMatrix(curSS, MVM, NMVM);
    safe_glUniform3f(curSS.h_uColor, g_arcballColor[0], g_arcballColor[1], g_arcballColor[2]);
    g_sphere->draw(curSS);

    /* draw filled */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // draw filled again
  }
    else {
    Picker picker(invEyeRbt, curSS);
    g_world->accept(picker);
    glFlush();
    g_currentPickedRbtNode = picker.getRbtNodeAtXY(g_mouseClickX, g_mouseClickY);
    if ((g_currentPickedRbtNode == g_groundNode)||(g_currentPickedRbtNode == nullptr))//??????
            g_currentPickedRbtNode = g_skyNode; 
  }

}