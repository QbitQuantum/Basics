  void test_exp(const int fuzzy_bits)
  {
    // Use at least 8 resolution bits.
    // Use at least 7 range bits.

    BOOST_STATIC_ASSERT(-FixedPointType::resolution >= 8);
    BOOST_STATIC_ASSERT( FixedPointType::range      >= 7);

    const FixedPointType a1(+1L    );                                       const FloatPointType b1(+1L    );
    const FixedPointType a2(+2L    );                                       const FloatPointType b2(+2L    );
    const FixedPointType a3(+4.375L);                                       const FloatPointType b3(+4.375L);
    const FixedPointType a4(+1.125L);                                       const FloatPointType b4(+1.125L);
    const FixedPointType a5(-1.125L);                                       const FloatPointType b5(-1.125L);
    const FixedPointType a6(+0.875L);                                       const FloatPointType b6(+0.875L);
    const FixedPointType a7(FixedPointType( 1) /  3);                       const FloatPointType b7(FloatPointType( 1) /  3);
    const FixedPointType a8(FixedPointType(11) / 10);                       const FloatPointType b8(FloatPointType(11) / 10);
    const FixedPointType a9(boost::math::constants::phi<FixedPointType>()); const FloatPointType b9(boost::math::constants::phi<FloatPointType>());

    using std::exp;

    BOOST_CHECK_CLOSE_FRACTION(exp(a1), FixedPointType(exp(b1)), tolerance_maker<FixedPointType>(fuzzy_bits));
    BOOST_CHECK_CLOSE_FRACTION(exp(a2), FixedPointType(exp(b2)), tolerance_maker<FixedPointType>(fuzzy_bits));
    BOOST_CHECK_CLOSE_FRACTION(exp(a3), FixedPointType(exp(b3)), tolerance_maker<FixedPointType>(fuzzy_bits));
    BOOST_CHECK_CLOSE_FRACTION(exp(a4), FixedPointType(exp(b4)), tolerance_maker<FixedPointType>(fuzzy_bits));
    BOOST_CHECK_CLOSE_FRACTION(exp(a5), FixedPointType(exp(b5)), tolerance_maker<FixedPointType>(fuzzy_bits));
    BOOST_CHECK_CLOSE_FRACTION(exp(a6), FixedPointType(exp(b6)), tolerance_maker<FixedPointType>(fuzzy_bits));
    BOOST_CHECK_CLOSE_FRACTION(exp(a7), FixedPointType(exp(b7)), tolerance_maker<FixedPointType>(fuzzy_bits));
    BOOST_CHECK_CLOSE_FRACTION(exp(a8), FixedPointType(exp(b8)), tolerance_maker<FixedPointType>(fuzzy_bits));
    BOOST_CHECK_CLOSE_FRACTION(exp(a9), FixedPointType(exp(b9)), tolerance_maker<FixedPointType>(fuzzy_bits));
  }