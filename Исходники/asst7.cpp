static void drawStuff(bool picking) {
 
  // Declare an empty uniforms
  Uniforms uniforms;
  
  // if we are not translating, update arcball scale
  if (!(g_mouseMClickButton || (g_mouseLClickButton && g_mouseRClickButton) || (g_mouseLClickButton && !g_mouseRClickButton && g_spaceDown)))
    updateArcballScale();

  // build & send proj. matrix to vshader
  const Matrix4 projmat = makeProjectionMatrix();
  sendProjectionMatrix(uniforms, projmat);

  const RigTForm eyeRbt = getPathAccumRbt(g_world, getNodeForEye(g_activeEye));
  const RigTForm invEyeRbt = inv(eyeRbt);

  const Cvec3 eyeLight1 = getPathAccumRbt(g_world, g_light1Node).getTranslation();
  const Cvec3 eyeLight2 = getPathAccumRbt(g_world, g_light2Node).getTranslation();
  
  uniforms.put("uLight", eyeLight1);
  uniforms.put("uLight2", eyeLight2);
  
  if (!picking) {
	  Drawer drawer(invEyeRbt, uniforms);
	  g_world->accept(drawer);

	  if (g_displayArcball && shouldUseArcball()) {
		  drawArcBall(uniforms);
	  }
  } else {
	  Picker picker(invEyeRbt, uniforms);
	  
    // set overriding material to our picking material
    g_overridingMaterial = g_pickingMat;
    
    g_world->accept(picker);
    
    // unset overriding material 
    g_overridingMaterial.reset();
	  
    glFlush();
	  g_currentPickedRbtNode = picker.getRbtNodeAtXY(g_mouseClickX, g_mouseClickY);
	  
	  if (g_currentPickedRbtNode == g_groundNode) {
		  g_currentPickedRbtNode = shared_ptr<SgRbtNode>();   // set to NULL
		  cout << "clicked on ground\n";
	  }
  }
}