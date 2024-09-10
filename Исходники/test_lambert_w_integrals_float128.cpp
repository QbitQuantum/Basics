void test_integrals()
{
  // Integral of the Lambert W function:
  // https://en.wikipedia.org/wiki/Lambert_W_function
  using boost::math::quadrature::tanh_sinh;
  using boost::math::quadrature::exp_sinh;
  // file:///I:/modular-boost/libs/math/doc/html/math_toolkit/quadrature/double_exponential/de_tanh_sinh.html
  using std::sqrt;

  std::cout << "Integration of type " << typeid(Real).name()  << std::endl;

  Real tol = std::numeric_limits<Real>::epsilon();
  { //  // Integrate for function lambert_W0(z);
    tanh_sinh<Real> ts;
    Real a = 0;
    Real b = boost::math::constants::e<Real>();
    auto f = [](Real z)->Real
    {
      return lambert_w0<Real>(z);
    };
    Real z = ts.integrate(f, a, b); // OK without any decltype(f)
    BOOST_CHECK_CLOSE_FRACTION(z, boost::math::constants::e<Real>() - 1, tol);
  }
  {
    // Integrate for function lambert_W0(z/(z sqrt(z)).
    exp_sinh<Real> es;
    auto f = [](Real z)->Real
    {
      return lambert_w0<Real>(z)/(z * sqrt(z));
    };
    Real z = es.integrate(f); // OK
    BOOST_CHECK_CLOSE_FRACTION(z, 2 * boost::math::constants::root_two_pi<Real>(), tol);
  }
  {
    // Integrate for function lambert_W0(1/z^2).
    exp_sinh<Real> es;
    //const Real sqrt_min = sqrt(boost::math::tools::min_value<Real>()); // 1.08420217e-19 fo 32-bit float.
    // error C3493: 'sqrt_min' cannot be implicitly captured because no default capture mode has been specified
    auto f = [](Real z)->Real
    {
      if (z <= sqrt(boost::math::tools::min_value<Real>()) )
      { // Too small would underflow z * z and divide by zero to overflow 1/z^2 for lambert_w0 z parameter.
        return static_cast<Real>(0);
      }
      else
      {
        return lambert_w0<Real>(1 / (z * z)); // warning C4756: overflow in constant arithmetic, even though cannot happen.
      }
    };
    Real z = es.integrate(f);
    BOOST_CHECK_CLOSE_FRACTION(z, boost::math::constants::root_two_pi<Real>(), tol);
  }
} // template<class Real> void test_integrals()