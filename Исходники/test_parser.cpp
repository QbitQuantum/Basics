    s = "4^2/2+2";
    res = parse(s);
    REQUIRE(eq(*res, *integer(10)));

    s = "(1+2*(3+1)-5/(2+2))";
    res = parse(s);
    REQUIRE(eq(*res, *add(integer(9), div(integer(-5), integer(4)))));

    s = "2 + -3";
    res = parse(s);
    REQUIRE(eq(*res, *integer(-1)));

    s = "10000000000000000000000000";
    res = parse(s);
    REQUIRE(eq(*res, *pow(integer(10), integer(25))));

    // Make sure that parsing and printing works correctly
    s = "0.123123123e-10";
    res = parse(s);
    REQUIRE(eq(*res, *parse(res->__str__())));

    s = "123123123123123.";
    res = parse(s);
    REQUIRE(eq(*res, *parse(res->__str__())));

#ifdef HAVE_SYMENGINE_MPFR
    s = "1.231231232123123123123123123123e8";
    res = parse(s);
    REQUIRE(eq(*res, *parse(res->__str__())));
#endif