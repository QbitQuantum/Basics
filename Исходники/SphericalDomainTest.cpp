void SphericalDomainTest::check_closest_pt( const SphericalDomain& dom, 
                                            const Vector3D& input_pt,
                                            const Vector3D& output_pt )
{
  Vector3D vo = output_pt - dom.center();
  Vector3D vi = input_pt  - dom.center();
  CPPUNIT_ASSERT_DOUBLES_EQUAL( dom.radius(), vo.length(), 1e-6 );
  vi *= dom.radius() / vi.length();
  CPPUNIT_ASSERT_VECTORS_EQUAL( vo, vi, 1e-6 );
}