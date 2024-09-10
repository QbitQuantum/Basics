void CacheGeometryRenderer::Initialize(int noPts, int noFaces, double *points,
                                       int *faces) const {
  (void)noPts; // Avoid compiler warning
  glBegin(GL_TRIANGLES);
  V3D normal;
  for (int i = 0; i < noFaces; i++) {
    int index1 = faces[i * 3] * 3;
    int index2 = faces[i * 3 + 1] * 3;
    int index3 = faces[i * 3 + 2] * 3;
    // Calculate normal and normalize
    V3D v1(points[index1], points[index1 + 1], points[index1 + 2]);
    V3D v2(points[index2], points[index2 + 1], points[index2 + 2]);
    V3D v3(points[index3], points[index3 + 1], points[index3 + 2]);
    normal = (v1 - v2).cross_prod(v2 - v3);
    normal.normalize();
    glNormal3d(normal[0], normal[1], normal[2]);
    glVertex3dv(points + index1);
    glVertex3dv(points + index2);
    glVertex3dv(points + index3);
  }
  glEnd();
}