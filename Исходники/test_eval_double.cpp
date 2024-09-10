TEST_CASE("eval_double: eval_double", "[eval_double]")
{
    RCP<const Basic> r1, r2, r3, r4;
    r1 = sin(integer(1));
    r2 = sin(div(integer(1), integer(2)));
    r3 = div(one, integer(5));
    r4 = integer(5);

    std::vector<std::pair<RCP<const Basic>, double>> vec = {
        { r1, 0.841470984808 },
        { r2, 0.479425538604 },
        { add(r1, r2), 1.320896523412 },
        { mul(r1, r2), 0.403422680111 },
        { pow(r1, r2), 0.920580670898 },
        { tan(pow(r1, r2)), 1.314847038576 },
        { add(sin(r3), add(cos(r4), add(tan(r3), add(sec(integer(6)), add(csc(r4), cot(r4)))))), 0.387875350057 },
        { add(asin(r3), add(acos(r3), add(atan(r3), add(asec(integer(6)), add(acsc(r4), acot(r4)))))), 3.570293614860 },
        { add(sinh(one), add(cosh(one), add(tanh(one), coth(one)))), 4.792911269914 },
        { add(asinh(r4), add(acosh(r4), add(atanh(r3), acoth(r4)))), 5.010335118942 },
        { SymEngine::abs(log(div(pi, mul(E, integer(2))))), 0.548417294710 },
        { SymEngine::atan2(r1, neg(r2)), 2.08867384922582 }
    };

    for (unsigned i = 0; i < vec.size(); i++) {
        double val = eval_double(*vec[i].first);
        std::cout.precision(12);
        std::cout << vec[i].first->__str__() << " ~ " << val << std::endl;
        REQUIRE(::fabs(val - vec[i].second) < 1e-12);
    }
