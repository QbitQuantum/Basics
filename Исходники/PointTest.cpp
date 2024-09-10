// Normalization Tests
// Vector normalization can handle a Zero Magnitude
TEST_F(PointTest, NormZeroMag) {
  Point p = ZeroMag_;
  p = p.Normalize();
  ASSERT_TRUE(p.Equals(ZeroMag_)) << "Normalize 0 vector !=  0 vector";
  ASSERT_EQ(p.Magnitude(), 0)  << "Normalize 0 vector: Mag != 0";
}