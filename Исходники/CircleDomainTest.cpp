void CircleDomainTest::test_snap_to()
{
  Vector3D origin(0,0,0);
  Vector3D z(0,0,1);
  double rad1 = 4.0/3.0;
  CircleDomain dom1( origin, z, rad1 );
  Vector3D pt( 1, 0, 0 );
  dom1.snap_to( 0, pt );
  CPPUNIT_ASSERT_VECTORS_EQUAL( Vector3D(rad1,0,0), pt, 1e-6 );
  Vector3D a = Vector3D( 1, 2, 3 );
  pt = a;
  dom1.snap_to( 0, pt );
  a = Vector3D( 1, 2, 0 );
  a *= rad1 / a.length();
  CPPUNIT_ASSERT_VECTORS_EQUAL( a, pt, 1e-6 );
  
  Vector3D some_pt(5,-1,6);
  Vector3D some_dir(-5,-4,1);
  double rad2 = 1.0;
  CircleDomain dom2( some_pt, some_dir, rad2 );
  
  a = Vector3D( 0, 0, 0);
  pt = a;
  dom2.snap_to( 0, pt );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( rad2, (pt - some_pt).length(), 1e-6 ); // rad from center
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, (pt - some_pt) % some_dir, 1e-6 );// in plane
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, ((pt - some_pt) * (a - some_pt)) % some_dir, 1e-6 ); // correct direction from center

  a = Vector3D( 0, -1, -2 );
  pt = a;
  dom2.snap_to( 0, pt );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( rad2, (pt - some_pt).length(), 1e-6 ); // rad from center
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, (pt - some_pt) % some_dir, 1e-6 );// in plane
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, ((pt - some_pt) * (a - some_pt)) % some_dir, 1e-6 ); // correct direction from center
}