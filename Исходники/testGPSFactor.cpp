//***************************************************************************
TEST(GPSData, init) {

  // GPS Reading 1 will be ENU origin
  double t1 = 84831;
  Point3 NED1(0, 0, 0);
  LocalCartesian enu(35.4393283333333, -119.062986666667, 275.54,
      Geocentric::WGS84);

  // GPS Readin 2
  double t2 = 84831.5;
  double E, N, U;
  enu.Forward(35.4394633333333, -119.063146666667, 276.52, E, N, U);
  Point3 NED2(N, E, -U);

  // Estimate initial state
  Pose3 T;
  Vector3 nV;
  boost::tie(T, nV) = GPSFactor::EstimateState(t1, NED1, t2, NED2, 84831.0796);

  // Check values values
  EXPECT(assert_equal((Vector )Vector3(29.9575, -29.0564, -1.95993), nV, 1e-4));
  EXPECT( assert_equal(Rot3::ypr(-0.770131, 0.046928, 0), T.rotation(), 1e-5));
  Point3 expectedT(2.38461, -2.31289, -0.156011);
  EXPECT(assert_equal(expectedT, T.translation(), 1e-5));
}