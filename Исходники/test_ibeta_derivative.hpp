void test_spots(T)
{
   using std::ldexp;
   T tolerance = boost::math::tools::epsilon<T>() * 40000;
      BOOST_CHECK_CLOSE(
         ::boost::math::ibeta_derivative(
            static_cast<T>(2),
            static_cast<T>(4),
            ldexp(static_cast<T>(1), -557)),
         static_cast<T>(4.23957586190238472641508753637420672781472122471791800210e-167L), tolerance * 4);
      BOOST_CHECK_CLOSE(
         ::boost::math::ibeta_derivative(
            static_cast<T>(2),
            static_cast<T>(4.5),
            ldexp(static_cast<T>(1), -557)),
         static_cast<T>(5.24647512910420109893867082626308082567071751558842352760e-167L), tolerance * 4);
}