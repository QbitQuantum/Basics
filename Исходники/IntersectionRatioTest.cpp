void testPointUnitSphere( const math::Vector3<real_t> & p )
{
   static const geometry::Sphere UNIT_SPHERE( math::Vector3<real_t>( 0, 0, 0 ), real_t( 1 ) );
   static const real_t EPSILON = real_t(1e-4);

   real_t q = lbm::intersectionRatioBisection( UNIT_SPHERE, p, -p, EPSILON );
   
   Vector3<real_t> intersectionPoint = p + (-p) * q;
   real_t intersectionRadius = intersectionPoint.length();

   WALBERLA_CHECK_LESS( std::fabs( intersectionRadius - real_t( 1 ) ), EPSILON );

   q = lbm::intersectionRatioSphere( UNIT_SPHERE, p, -p );
   
   intersectionPoint = p + ( -p ) * q;
   intersectionRadius = intersectionPoint.length();
   
   WALBERLA_CHECK_LESS( std::fabs( intersectionRadius - real_t( 1 ) ), EPSILON );
   
   q = lbm::intersectionRatio( UNIT_SPHERE, p, -p, EPSILON );
   
   intersectionPoint = p + ( -p ) * q;
   intersectionRadius = intersectionPoint.length();
   
   WALBERLA_CHECK_LESS( std::fabs( intersectionRadius - real_t( 1 ) ), EPSILON );
}