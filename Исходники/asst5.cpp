static void drawStuff(const ShaderState& curSS, bool picking) {
  // build & send proj. matrix to vshader
  const Matrix4 projmat = makeProjectionMatrix();
  sendProjectionMatrix(curSS, projmat);

  // Choose an eye camera
  // changed to shared_ptr in hw4
  switch(CHOOSEN_FRAME){
    case 0:
      g_currentView = g_skyNode;
      break;
    case 1:
      g_currentView = g_robot1Node;
      break;
    case 2:
      g_currentView = g_robot2Node;
      break;
  }

  const RigTForm eyeRbt = getPathAccumRbt(g_world, g_currentView);
  const RigTForm invEyeRbt = inv(eyeRbt);

  const Cvec3 eyeLight1 = Cvec3(invEyeRbt * Cvec4(g_light1, 1)); // g_light1 position in eye coordinates
  const Cvec3 eyeLight2 = Cvec3(invEyeRbt * Cvec4(g_light2, 1)); // g_light2 position in eye coordinates
  safe_glUniform3f(curSS.h_uLight, eyeLight1[0], eyeLight1[1], eyeLight1[2]);
  safe_glUniform3f(curSS.h_uLight2, eyeLight2[0], eyeLight2[1], eyeLight2[2]);

  if (!picking) {
    Drawer drawer(invEyeRbt, curSS);
    g_world->accept(drawer);

    // draw a sphere?
    if(!DRAW_SPHERE){return;}    
    if(!WORLD_SKY && !g_currentPickedRbtNode){return;}
    
    RigTForm sphere_center = getPathAccumRbt(g_world, g_currentPickedRbtNode);
    RigTForm eyeCord = invEyeRbt * sphere_center; 
    sphere_center_eyeCord = eyeCord.getTranslation();

    if (!(g_mouseMClickButton || (g_mouseLClickButton && g_mouseRClickButton))){ 
      g_arcballScale = getScreenToEyeScale(sphere_center_eyeCord[2], g_frustFovY, g_windowHeight);
    }
    double arcball_radius = g_arcballScale * g_arcballScreenRadius;

    // draw sphere
    // ----------
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Matrix4 MVM = rigTFormToMatrix(eyeCord) * Matrix4::makeScale(Cvec3(arcball_radius, arcball_radius, arcball_radius));
    Matrix4 NMVM = normalMatrix(MVM);
    sendModelViewNormalMatrix(curSS, MVM, NMVM);
    safe_glUniform3f(curSS.h_uColor, 0, 0, 0);
    g_sphere->draw(curSS);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  }
  else{
    Picker picker(invEyeRbt, curSS);
    g_world->accept(picker);
    glFlush();
    g_currentPickedRbtNode = picker.getRbtNodeAtXY(g_mouseClickX, g_mouseClickY);
    if (g_currentPickedRbtNode == g_groundNode)
      g_currentPickedRbtNode = shared_ptr<SgRbtNode>(); 
  }  

}