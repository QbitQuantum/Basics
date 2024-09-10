TEST(TinyMatrix, LookAt) {
  // 简单的正交验证
  Vec3 e; e[0]= 1; e[1] = 2; e[2] = 3;
  Mat3 R = LookAt(e);//这个R是旋转矩阵，则R为正交矩阵，R与R的转置相乘为单位阵
  Mat3 I = Mat3::Identity();
  Mat3 RRT = R*R.transpose();
  Mat3 RTR = R.transpose()*R;

  EXPECT_MATRIX_NEAR(I, RRT, 1e-15);
  EXPECT_MATRIX_NEAR(I, RTR, 1e-15);
}