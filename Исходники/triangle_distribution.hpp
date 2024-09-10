    result_type operator()()
    {
#ifndef BOOST_NO_STDC_NAMESPACE
        using std::sqrt;
#endif
        result_type u = _rng();
        if( u <= q1 )
            return _a + p1*sqrt(u);
        else
            return _c - d3*sqrt(d2*u-d1);
    }