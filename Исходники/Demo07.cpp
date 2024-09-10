void renderScene(void) {
  int sx = glutGet(GLUT_WINDOW_WIDTH);
  int sy = glutGet(GLUT_WINDOW_HEIGHT);
  //SAspect = Scaling(1, (float)sx / sy, 1);
  VECTOR4D worldRayOrigin, worldRayDir;
  VECTOR4D modelRayOrigin, modelRayDir;
  MATRIX4D InvW;
  multimap<float, CMesh::INTERSECTIONINFO> faces;
  bool fill = false;

  SAspect = Scaling((float)sy / sx, 1, 1);
  W = Identity();

  P = PerspectiveWidthHeightRH(0.5f, 0.5f, 1.0f, 10.0f);
  EC = SAspect * T * Translation(0.0f, 0.0f, -1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  BuildRayFromPerspective(EC, mx, my, worldRayOrigin, worldRayDir);
  Inverse(W, InvW);
  modelRayOrigin = InvW * worldRayOrigin;
  modelRayDir = InvW * worldRayDir;
  fill = g_EggCarton.RayCast(modelRayOrigin, modelRayDir, faces);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_TRIANGLES);
  g_EggCarton.Draw(EC);
  glEnd();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  if (fill)
    g_EggCarton.Draw(EC, faces.begin()->second.Face, 1);
  glEnd();

  if (bWireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  g_Plate.Draw(SAspect * T * Translation(0.0f, 0.0f, -0.1f));
  g_Sphere.Draw(SAspect * T * Translation(0.4f, 0.4f, 0.32f));
  g_Bananas.Draw(SAspect * T * Translation(0.45f, 0.45f, 0.48f));
  g_Flower.Draw(SAspect * T * Translation(-0.5f, 0.5f, 0.8f));
  glEnd();

  glutSwapBuffers();
}