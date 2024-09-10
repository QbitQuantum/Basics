RealType generate_canonical_impl(URNG& g, boost::mpl::false_ /*is_integral*/)
{
    using std::pow;
    using std::floor;
    BOOST_ASSERT((g.min)() == 0);
    BOOST_ASSERT((g.max)() == 1);
    std::size_t digits = std::numeric_limits<RealType>::digits;
    std::size_t engine_bits = detail::generator_bits<URNG>::value();
    std::size_t b = (std::min)(bits, digits);
    RealType R = pow(RealType(2), RealType(engine_bits));
    RealType mult = R;
    RealType limit = pow(RealType(2), RealType(b));
    RealType S = RealType(g() - (g.min)());
    while(mult < limit) {
        RealType inc(floor((RealType(g()) - RealType((g.min)())) * R));
        S += inc * mult;
        mult *= R;
    }
    return S / mult;
}