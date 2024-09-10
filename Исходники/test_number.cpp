    REQUIRE(is_a<RealMPFR>(*divnum(r3, rat1)));
    REQUIRE(eq(*r1, *divnum(r3, r1)));
    REQUIRE(is_a<RealMPFR>(*divnum(mulnum(rat1, rat1), r1)));
    REQUIRE(eq(*r1, *divnum(mulnum(rd1, rd1), r1)));
    REQUIRE(eq(*divnum(i1, r1), *divnum(i2, r2)));
    REQUIRE(eq(*r1, *subnum(r2, r1)));
    REQUIRE(eq(*r1, *subnum(integer(20), r1)));
    REQUIRE(eq(*r1, *mulnum(r2, half)));
    REQUIRE(eq(*r3, *pownum(r1, i2)));
    REQUIRE(eq(*r4, *pownum(i2, r1)));
    REQUIRE(eq(*r1, *pownum(r3, half)));
    REQUIRE(eq(*r3, *pownum(r1, real_double(2.0))));
    REQUIRE(eq(*r3, *pownum(r1, divnum(r2, r1))));
    REQUIRE(eq(*r4, *pownum(real_double(2.0), r1)));
    REQUIRE(is_a<RealMPFR>(*pownum(rat1, r1)));
    REQUIRE(eq(*divnum(i1, r4), *half->pow(*r1)));

    mpfr_class e(100);
    mpfr_set_ui(e.get_mpfr_t(), 10, MPFR_RNDN);
    r2 = real_mpfr(std::move(e));
    REQUIRE(r1->__hash__() == r2->__hash__());
    REQUIRE(r1->compare(*r2) == 0);
    REQUIRE(r1->compare(*r3) == -1);
    REQUIRE(r3->compare(*r2) == 1);

    // to increase coverage
    mpfr_class ee(10);
    mpfr_set_ui(ee.get_mpfr_t(), 101, MPFR_RNDN);
    r2 = real_mpfr(std::move(ee));
    REQUIRE(r1->compare(*r2) == 1); // TO-DO is this is a bug or what ?
