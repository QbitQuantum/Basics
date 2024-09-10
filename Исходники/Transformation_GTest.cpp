TEST_F(GeometryFixture, AlignFaceTransformations)
{
  double tol = 1.0E-12;

  Point3dVector vertices(4);
  vertices[0] = Point3d(1, 0, 1);
  vertices[1] = Point3d(1, 0, 0);
  vertices[2] = Point3d(2, 0, 0);
  vertices[3] = Point3d(2, 0, 1);
  Point3dVector testVertices;
  Point3dVector tempVertices;
  Transformation T;

  // rotate 0 degrees about z
  testVertices = Transformation::rotation(Vector3d(0,0,1), 0)*vertices;
  T = Transformation::alignFace(testVertices);
  tempVertices = T.inverse()*testVertices;
  EXPECT_NEAR(0, tempVertices[0].x(), tol);
  EXPECT_NEAR(1, tempVertices[0].y(), tol);
  EXPECT_NEAR(0, tempVertices[0].z(), tol);
  EXPECT_NEAR(0, tempVertices[1].x(), tol);
  EXPECT_NEAR(0, tempVertices[1].y(), tol);
  EXPECT_NEAR(0, tempVertices[1].z(), tol);
  EXPECT_NEAR(1, tempVertices[2].x(), tol);
  EXPECT_NEAR(0, tempVertices[2].y(), tol);
  EXPECT_NEAR(0, tempVertices[2].z(), tol);
  EXPECT_NEAR(1, tempVertices[3].x(), tol);
  EXPECT_NEAR(1, tempVertices[3].y(), tol);
  EXPECT_NEAR(0, tempVertices[3].z(), tol);

  // rotate 30 degrees about z
  testVertices = Transformation::rotation(Vector3d(0,0,1), degToRad(30))*vertices;
  T = Transformation::alignFace(testVertices);
  tempVertices = T.inverse()*testVertices;
  EXPECT_NEAR(0, tempVertices[0].x(), tol);
  EXPECT_NEAR(1, tempVertices[0].y(), tol);
  EXPECT_NEAR(0, tempVertices[0].z(), tol);
  EXPECT_NEAR(0, tempVertices[1].x(), tol);
  EXPECT_NEAR(0, tempVertices[1].y(), tol);
  EXPECT_NEAR(0, tempVertices[1].z(), tol);
  EXPECT_NEAR(1, tempVertices[2].x(), tol);
  EXPECT_NEAR(0, tempVertices[2].y(), tol);
  EXPECT_NEAR(0, tempVertices[2].z(), tol);
  EXPECT_NEAR(1, tempVertices[3].x(), tol);
  EXPECT_NEAR(1, tempVertices[3].y(), tol);
  EXPECT_NEAR(0, tempVertices[3].z(), tol);

  // rotate -30 degrees about z
  testVertices = Transformation::rotation(Vector3d(0,0,1), -degToRad(30))*vertices;
  T = Transformation::alignFace(testVertices);
  tempVertices = T.inverse()*testVertices;
  EXPECT_NEAR(0, tempVertices[0].x(), tol);
  EXPECT_NEAR(1, tempVertices[0].y(), tol);
  EXPECT_NEAR(0, tempVertices[0].z(), tol);
  EXPECT_NEAR(0, tempVertices[1].x(), tol);
  EXPECT_NEAR(0, tempVertices[1].y(), tol);
  EXPECT_NEAR(0, tempVertices[1].z(), tol);
  EXPECT_NEAR(1, tempVertices[2].x(), tol);
  EXPECT_NEAR(0, tempVertices[2].y(), tol);
  EXPECT_NEAR(0, tempVertices[2].z(), tol);
  EXPECT_NEAR(1, tempVertices[3].x(), tol);
  EXPECT_NEAR(1, tempVertices[3].y(), tol);
  EXPECT_NEAR(0, tempVertices[3].z(), tol);

  // rotate -30 degrees about x
  testVertices = Transformation::rotation(Vector3d(1,0,0), -degToRad(30))*vertices;
  T = Transformation::alignFace(testVertices);
  tempVertices = T.inverse()*testVertices;
  EXPECT_NEAR(0, tempVertices[0].x(), tol);
  EXPECT_NEAR(1, tempVertices[0].y(), tol);
  EXPECT_NEAR(0, tempVertices[0].z(), tol);
  EXPECT_NEAR(0, tempVertices[1].x(), tol);
  EXPECT_NEAR(0, tempVertices[1].y(), tol);
  EXPECT_NEAR(0, tempVertices[1].z(), tol);
  EXPECT_NEAR(1, tempVertices[2].x(), tol);
  EXPECT_NEAR(0, tempVertices[2].y(), tol);
  EXPECT_NEAR(0, tempVertices[2].z(), tol);
  EXPECT_NEAR(1, tempVertices[3].x(), tol);
  EXPECT_NEAR(1, tempVertices[3].y(), tol);
  EXPECT_NEAR(0, tempVertices[3].z(), tol);

  // rotate -90 degrees about x
  testVertices = Transformation::rotation(Vector3d(1,0,0), -degToRad(90))*vertices;
  T = Transformation::alignFace(testVertices);
  tempVertices = T.inverse()*testVertices;
  EXPECT_NEAR(1, tempVertices[0].x(), tol);
  EXPECT_NEAR(0, tempVertices[0].y(), tol);
  EXPECT_NEAR(0, tempVertices[0].z(), tol);
  EXPECT_NEAR(1, tempVertices[1].x(), tol);
  EXPECT_NEAR(1, tempVertices[1].y(), tol);
  EXPECT_NEAR(0, tempVertices[1].z(), tol);
  EXPECT_NEAR(0, tempVertices[2].x(), tol);
  EXPECT_NEAR(1, tempVertices[2].y(), tol);
  EXPECT_NEAR(0, tempVertices[2].z(), tol);
  EXPECT_NEAR(0, tempVertices[3].x(), tol);
  EXPECT_NEAR(0, tempVertices[3].y(), tol);
  EXPECT_NEAR(0, tempVertices[3].z(), tol);

  // rotate 30 degrees about x
  testVertices = Transformation::rotation(Vector3d(1,0,0), degToRad(30))*vertices;
  T = Transformation::alignFace(testVertices);
  tempVertices = T.inverse()*testVertices;
  EXPECT_NEAR(0, tempVertices[0].x(), tol);
  EXPECT_NEAR(1, tempVertices[0].y(), tol);
  EXPECT_NEAR(0, tempVertices[0].z(), tol);
  EXPECT_NEAR(0, tempVertices[1].x(), tol);
  EXPECT_NEAR(0, tempVertices[1].y(), tol);
  EXPECT_NEAR(0, tempVertices[1].z(), tol);
  EXPECT_NEAR(1, tempVertices[2].x(), tol);
  EXPECT_NEAR(0, tempVertices[2].y(), tol);
  EXPECT_NEAR(0, tempVertices[2].z(), tol);
  EXPECT_NEAR(1, tempVertices[3].x(), tol);
  EXPECT_NEAR(1, tempVertices[3].y(), tol);
  EXPECT_NEAR(0, tempVertices[3].z(), tol);

  // rotate 90 degrees about x
  testVertices = Transformation::rotation(Vector3d(1,0,0), degToRad(90))*vertices;
  T = Transformation::alignFace(testVertices);
  tempVertices = T.inverse()*testVertices;
  EXPECT_NEAR(1, tempVertices[0].x(), tol);
  EXPECT_NEAR(0, tempVertices[0].y(), tol);
  EXPECT_NEAR(0, tempVertices[0].z(), tol);
  EXPECT_NEAR(1, tempVertices[1].x(), tol);
  EXPECT_NEAR(1, tempVertices[1].y(), tol);
  EXPECT_NEAR(0, tempVertices[1].z(), tol);
  EXPECT_NEAR(0, tempVertices[2].x(), tol);
  EXPECT_NEAR(1, tempVertices[2].y(), tol);
  EXPECT_NEAR(0, tempVertices[2].z(), tol);
  EXPECT_NEAR(0, tempVertices[3].x(), tol);
  EXPECT_NEAR(0, tempVertices[3].y(), tol);
  EXPECT_NEAR(0, tempVertices[3].z(), tol);
}