TEST_F(GraphicsLightTest, TestLightGet) {
  Vector param;

  glClearColor(0.f, 0.f, 0.f, 0.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const float pos[] = {1.f, 2.f, 3.f, 1.f};
  const float dir[] = {0.f, 0.f, -1.f, 0.f};
  const float att[] = {0.01f, 0.02f, 0.03f};
  const float spot[] = {60.f, 128.f};

  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, kRed);
  glLightfv(GL_LIGHT0, GL_AMBIENT, kBlue);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spot[0]);
  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spot[1]);
  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att[0]);
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att[1]);
  glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att[2]);

  Vector position = GetLightParameter(GL_LIGHT0, GL_POSITION);
  Vector direction = GetLightParameter(GL_LIGHT0, GL_SPOT_DIRECTION);
  Vector diffuse = GetLightParameter(GL_LIGHT0, GL_DIFFUSE);
  Vector ambient = GetLightParameter(GL_LIGHT0, GL_AMBIENT);
  Vector cutoff = GetLightParameter(GL_LIGHT0, GL_SPOT_CUTOFF);
  Vector exponent = GetLightParameter(GL_LIGHT0, GL_SPOT_EXPONENT);
  Vector constant = GetLightParameter(GL_LIGHT0, GL_CONSTANT_ATTENUATION);
  Vector linear = GetLightParameter(GL_LIGHT0, GL_LINEAR_ATTENUATION);
  Vector quadratic = GetLightParameter(GL_LIGHT0, GL_QUADRATIC_ATTENUATION);

  for (size_t i = 0; i < Vector::kEntries; ++i) {
    EXPECT_EQ(position.Get(i), pos[i]);
    EXPECT_EQ(direction.Get(i), dir[i]);
    EXPECT_EQ(diffuse.Get(i), kRed[i]);
    EXPECT_EQ(ambient.Get(i), kBlue[i]);
  }
  EXPECT_EQ(cutoff.Get(0), spot[0]);
  EXPECT_EQ(exponent.Get(0), spot[1]);
  EXPECT_EQ(constant.Get(0), att[0]);
  EXPECT_EQ(linear.Get(0), att[1]);
  EXPECT_EQ(quadratic.Get(0), att[2]);

  // Change to directional light.
  float pos2[] = {1.f, 2.f, 3.f, 0.f};
  glLightfv(GL_LIGHT0, GL_POSITION, pos2);
  position = GetLightParameter(GL_LIGHT0, GL_POSITION);
  for (size_t i = 0; i < Vector::kEntries; ++i) {
    EXPECT_EQ(position.Get(i), pos2[i]);
  }

  // Change back to spot light, but at a position/direction
  // specified by the model-view matrix.
  Matrix mx;
  const Vector trans(5.f, 6.f, 7.f, 1.f);
  const Vector axis(1.f, 0.f, 0.f, 0.f);
  mx.AssignMatrixMultiply(mx, Matrix::GenerateTranslation(trans));
  mx.AssignMatrixMultiply(mx, Matrix::GenerateRotationByDegrees(45.f, axis));

  float glmx[Matrix::kEntries];
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(mx.GetColumnMajorArray(glmx));

  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
  position = GetLightParameter(GL_LIGHT0, GL_POSITION);
  direction = GetLightParameter(GL_LIGHT0, GL_SPOT_DIRECTION);

  mx.Inverse();
  position.AssignMatrixMultiply(mx, position);
  direction.AssignMatrixMultiply(mx, direction);

  const float tolerance = 1.0e-6f;
  for (size_t i = 0; i < Vector::kEntries; ++i) {
    EXPECT_NEAR(position.Get(i), pos[i], tolerance);
  }
  for (int i = 0; i < 3; ++i) {
    EXPECT_NEAR(direction.Get(i), dir[i], tolerance);
  }
  EXPECT_IMAGE();
}