/**
 * Creates a Cube
 * @param Point1 :: first point of the cube
 * @param Point2 :: second point of the cube
 * @param Point3 :: thrid point of the cube
 * @param Point4 :: fourth point of the cube
 */
void GluGeometryRenderer::CreateCube(const V3D &Point1, const V3D &Point2,
                                     const V3D &Point3, const V3D &Point4) {
  V3D vec0 = Point1;
  V3D vec1 = Point2 - Point1;
  V3D vec2 = Point3 - Point1;
  V3D vec3 = Point4 - Point1;
  V3D vertex[8];
  vertex[0] = vec0;
  vertex[1] = vec0 + vec3;
  vertex[2] = vec0 + vec3 + vec1;
  vertex[3] = vec0 + vec1;
  vertex[4] = vec0 + vec2;
  vertex[5] = vec0 + vec2 + vec3;
  vertex[6] = vec0 + vec2 + vec3 + vec1;
  vertex[7] = vec0 + vec1 + vec2;
  // int
  // faceindex[6][4]={{0,1,2,3},{0,3,7,4},{3,2,6,7},{2,1,5,6},{0,4,5,1},{4,7,6,5}};
  // int
  // faceindex[6][4]={{0,3,2,1},{0,4,7,3},{3,7,6,2},{2,6,5,1},{0,1,5,4},{4,5,6,7}};
  int faceindex[6][4] = {
      {0, 1, 2, 3}, // top
      {0, 3, 7, 4}, // left
      {3, 2, 6, 7}, // back
      {2, 1, 5, 6}, // right
      {0, 4, 5, 1}, // front
      {4, 7, 6, 5}, // bottom
  };
  V3D normal;
  // first face
  glBegin(GL_QUADS);
  for (auto &row : faceindex) {
    normal = (vertex[row[0]] - vertex[row[1]])
                 .cross_prod((vertex[row[0]] - vertex[row[2]]));
    normal.normalize();
    glNormal3d(normal[0], normal[1], normal[2]);
    for (int j = 0; j < 4; j++) {
      int ij = row[j];
      if (ij == 0)
        glTexCoord2i(0, 0);
      if (ij == 1)
        glTexCoord2i(1, 0);
      if (ij == 2)
        glTexCoord2i(1, 1);
      if (ij == 3)
        glTexCoord2i(0, 1);
      if (ij == 4)
        glTexCoord2i(0, 0);
      if (ij == 5)
        glTexCoord2i(1, 0);
      if (ij == 6)
        glTexCoord2i(1, 1);
      if (ij == 7)
        glTexCoord2i(0, 1);
      glVertex3d(vertex[ij][0], vertex[ij][1], vertex[ij][2]);
    }
  }
  glEnd();
}