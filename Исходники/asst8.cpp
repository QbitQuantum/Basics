static void drawStuff(bool picking) {

  Uniforms uniforms;

  // build & send proj. matrix to vshader
  const Matrix4 projmat = makeProjectionMatrix();
  sendProjectionMatrix(uniforms, projmat);

  // choose frame to use as eyeRbt
  RigTForm eyeRbt = getPathAccumRbt(g_world, g_eyeFrameNode);
  
  const RigTForm invEyeRbt = inv(eyeRbt);

  // get world space coordinates of the light
  Cvec3 light1 = getPathAccumRbt(g_world, g_light1Node).getTranslation();
  // transform to eye space, and set to uLight uniform
  uniforms.put("uLight", Cvec3(invEyeRbt * Cvec4(light1, 1)));

  Cvec3 light2 = getPathAccumRbt(g_world, g_light2Node).getTranslation();
  // transform to eye space, and set to uLight uniform
  uniforms.put("uLight2", Cvec3(invEyeRbt * Cvec4(light2, 1)));

   /*
  const Cvec3 eyeLight1 = Cvec3(invEyeRbt * Cvec4(g_light1, 1)); // g_light1 position in eye coordinates
  const Cvec3 eyeLight2 = Cvec3(invEyeRbt * Cvec4(g_light2, 1)); // g_light2 position in eye coordinates
  // safe_glUniform3f(curSS.h_uLight, eyeLight1[0], eyeLight1[1], eyeLight1[2]);
  // safe_glUniform3f(curSS.h_uLight2, eyeLight2[0], eyeLight2[1], eyeLight2[2]);
  uniforms.put("uLight", eyeLight1);
  uniforms.put("uLight2", eyeLight2);
  */

  RigTForm arcballRbt = makeArcballRbt();

  if(!(g_mouseMClickButton || (g_mouseLClickButton && g_mouseRClickButton) || (g_mouseLClickButton && !g_mouseRClickButton && g_spaceDown))){

    // update arcballScale
    g_arcballScale = getScreenToEyeScale((invEyeRbt * arcballRbt).getTranslation()[2], g_frustFovY, g_windowHeight);
  }

  if (!picking) {

    Drawer drawer(invEyeRbt, uniforms);
    g_world->accept(drawer);

    // draw arcball as part of asst3
    if (g_arcballVisible) {
  
      double s = g_arcballScale * g_arcballScreenRadius;

      RigTForm MVMrbt = invEyeRbt * arcballRbt;
      Matrix4 MVM = rigTFormToMatrix(MVMrbt);
      MVM = MVM * Matrix4::makeScale(Cvec3(s, s, s));
  
      Matrix4 NMVM = normalMatrix(MVM);
      sendModelViewNormalMatrix(uniforms, MVM, NMVM);
      
      g_arcballMat->draw(*g_sphere, uniforms);

    }

  } else {//if indeed picking

    Picker picker(invEyeRbt, uniforms);
    g_overridingMaterial = g_pickingMat;
    g_world->accept(picker);
    g_overridingMaterial.reset();

    glFlush();

    g_currentPickedRbtNode = picker.getRbtNodeAtXY(g_mouseClickX, g_mouseClickY);

    if (!g_currentPickedRbtNode || g_currentPickedRbtNode == g_groundNode)
      g_currentPickedRbtNode = g_eyeFrameNode;

    g_arcballVisible = (g_currentPickedRbtNode != g_eyeFrameNode || (g_currentPickedRbtNode == g_skyNode && g_skyModMode == 0));
    g_arcballScale = getScreenToEyeScale((invEyeRbt * arcballRbt).getTranslation()[2], g_frustFovY, g_windowHeight);
  } 
}