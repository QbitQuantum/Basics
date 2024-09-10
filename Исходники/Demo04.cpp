void renderScene(void) {
  int sx = glutGet(GLUT_WINDOW_WIDTH);
  int sy = glutGet(GLUT_WINDOW_HEIGHT);
  MATRIX4D SAspect = Scaling((float)sy / sx, 1, 1);
  //MATRIX4D SAspect = Scaling(1, (float)sx / sy, 1);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(bWireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glBegin(GL_TRIANGLES);
    g_EggCarton.Draw(SAspect * T * Translation(0.0f, 0.0f, -1.0f));
    g_Plate.Draw(SAspect * T * Translation(0.0f, 0.0f, -0.1f));
    g_Sphere.Draw(SAspect * T * Translation(0.4f, 0.4f, 0.32f));
    g_Bananas.Draw(SAspect * T * Translation(0.45f, 0.45f, 0.48f));
    g_Flower.Draw(SAspect * T * Translation(-0.5f, 0.5f, 0.8f));
  glEnd();

  glutSwapBuffers();
}