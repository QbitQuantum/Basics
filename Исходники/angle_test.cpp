// Clamping to a range that strattles pi should wrap to the boundary that's
// closest under modular arithmetic.
TEST_F(AngleTests, ClampModularAtNegativeCenterPositiveAngle) {
  const Angle a(kPi - 0.2f);
  const Angle center(kMinUniqueAngle);
  const Angle max_diff(0.1f);
  // This tests a positive number clamped to a range centered about a negative
  // number.
  EXPECT_FLOAT_EQ(a.Clamp(center, max_diff).ToRadians(),
                  (center - max_diff).ToRadians());
}