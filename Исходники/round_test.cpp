void test_rounding()
{
    // The first several blocks of tests use values with no more than
    // six significant decimal digits, six being a natural value for
    //   std::numeric_limits<float>::digits10
    // on an IEC 60559 machine.

    // Test rounding in (-1.0, 1.0).

    test_various_float_types(-0.999999L, -1.0L);
    test_various_float_types(-0.500001L, -1.0L);
    test_various_float_types(-0.500000L, -1.0L); // Away from zero.
    test_various_float_types(-0.499999L, -0.0L);
    test_various_float_types(-0.000001L, -0.0L);
    test_various_float_types(-0.000000L, -0.0L);
    test_various_float_types( 0.000000L,  0.0L);
    test_various_float_types( 0.000001L,  0.0L);
    test_various_float_types( 0.499999L,  0.0L);
    test_various_float_types( 0.500000L,  1.0L); // Away from zero.
    test_various_float_types( 0.500001L,  1.0L);
    test_various_float_types( 0.999999L,  1.0L);

    // Rounding to nearest: make sure halfway cases are rounded away
    // from zero.

    test_various_float_types(-4.5L, -5.0L);
    test_various_float_types(-3.5L, -4.0L);
    test_various_float_types(-2.5L, -3.0L);
    test_various_float_types(-1.5L, -2.0L);
    test_various_float_types(-0.5L, -1.0L);
    test_various_float_types( 0.5L,  1.0L);
    test_various_float_types( 1.5L,  2.0L);
    test_various_float_types( 2.5L,  3.0L);
    test_various_float_types( 3.5L,  4.0L);
    test_various_float_types( 4.5L,  5.0L);

    // The next block of tests uses values in the open interval
    //   (-1E29, +1E29)
    // which is well within the range of a float on an IEC 60559 machine
    // that uses the natural implementation such that
    //   std::numeric_limits<float>::max_exponent10
    // is 38.

    // Rounding an already-rounded integral value shouldn't change its
    // representation. Note however that some of these integers are
    // deliberately outside the range that can be exactly represented,
    // at least on a machine where
    //   std::numeric_limits<some-float-type)::digits10
    // is less than twenty-eight.

    test_various_float_types(-1234567890123456789012345678.0L, -1234567890123456789012345678.0L);
    test_various_float_types(-9876543200000000000000000000.0L, -9876543200000000000000000000.0L);
    test_various_float_types(-1000000000000000000000000000.0L, -1000000000000000000000000000.0L);
    test_various_float_types(-100001.0L, -100001.0L);
    test_various_float_types(-2.0L, -2.0L);
    test_various_float_types(-1.0L, -1.0L);
    test_various_float_types(-0.0L, -0.0L);
    test_various_float_types( 0.0L,  0.0L);
    test_various_float_types( 1.0L,  1.0L);
    test_various_float_types( 2.0L,  2.0L);
    test_various_float_types( 100001.0L,  100001.0L);
    test_various_float_types( 1000000000000000000000000000.0L,  1000000000000000000000000000.0L);
    test_various_float_types( 9876543200000000000000000000.0L,  9876543200000000000000000000.0L);
    test_various_float_types( 1234567890123456789012345678.0L,  1234567890123456789012345678.0L);

    // Test some numbers that are representable in all IEEE formats,
    // but not necessarily as exact integers because they have
    // FLT_DIG or DBL_DIG significant digits (and mantissae chosen
    // so that no more digits are accurately representable).
    test_various_float_types(987654.321L, 987654.0L);
    test_various_float_types(987654321098765.375L,  987654321098765.0L);
    test_various_float_types(987654321098765.500L,  987654321098766.0L);

    // Note: This test
//  test_various_float_types(987654321098765.4321L,  987654321098765.0L);
    // produces a 'failure' with type double on an intel machine using
    // ISO 60559 64-bit doubles (53-bit significand) when the rounding
    // direction is toward positive infinity. This is not a failure of
    // the algorithm, but rather an inherent limitation on precision.
    // The number to be rounded is not exactly representable as a double.
    // It is between 987654321098765.375 and 987654321098765.500, which
    // are exactly representable. The latter representation is chosen
    // only when the rounding direction is upward, and rounding it to
    // nearest correctly maps it to the next higher integer.
    //
    // Thus, the uncertainty due to [2.13.3/1] in the least significant
    // decimal digit of a number that is not exactly representable can
    // exceed four times epsilon. SOMEDAY !! It remains to establish
    // rigorous bounds, both overall and for each step.

    // The fifty-third Mersenne number was identified by the gnu octave
    // maintainers as a difficult case. See:
    //   http://article.gmane.org/gmane.comp.gnu.mingw.user/26299
    //     [2008-04-25T00:31:26Z from Tatsuro MATSUOKA]

    long double const M53 = 6361.0L * 69431.0L * 20394401.0L;

    test_various_float_types(      M53,  9007199254740991.0L);
    test_various_float_types(     -M53, -9007199254740991.0L);

    test_various_float_types( 1 +  M53,  9007199254740992.0L);
    test_various_float_types( 1 + -M53, -9007199254740990.0L);

    test_various_float_types(-1 +  M53,  9007199254740990.0L);
    test_various_float_types(-1 + -M53, -9007199254740992.0L);

    // Here is a similar testcase from François-Xavier Coudert,
    // who refers to:
    //   http://gcc.gnu.org/ml/gcc-patches/2006-10/msg00917.html
    // | 0.499999999999999944488848768742172978818416595458984375
    // | 4503599627370497.0
    // |
    // | They should be rounded to 0.0 and 4503599627370497.0, but
    // | simply adding 0.5 and truncating will round to 1.0 and
    // | 4503599627370498.
    //
    // The number above that's very close to one-half is in fact
    //   nextafter(0.5, 0.0)
    // both of which are ffffffffffffdf3f / 3fdfffffffffffff internally.

    test_various_float_types(4503599627370497.0L, 4503599627370497.0L);

    // This test:
//    test_various_float_types(nextafter(0.5L, 0.0L), 0.0L);
    // mustn't be run as such because, e.g., the value
    //   static_cast<float>(nextafter(0.5L, 0.0L))
    // need not be distinct from 0.0F.

    BOOST_TEST((test_one_case(nextafterf(0.5F, 0.0F), 0.0F)));
    BOOST_TEST((test_one_case(nextafter (0.5 , 0.0 ), 0.0 )));
    BOOST_TEST((test_one_case(nextafterl(0.5L, 0.0L), 0.0L)));
}