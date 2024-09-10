    r2 = mul(mul(i3, x), y);
    REQUIRE(eq(*r1, *r2));

    r1 = add(add(x, x), x);
    r2 = mul(i3, x);
    REQUIRE(eq(*r1, *r2));

    r1 = add(add(x, x), x);
    r2 = mul(x, i3);
    REQUIRE(eq(*r1, *r2));

    r1 = add(x, one);
    r2 = add(one, x);
    REQUIRE(eq(*r1, *r2));

    r1 = add(pow(x, y), z);
    r2 = add(z, pow(x, y));
    REQUIRE(eq(*r1, *r2));

    r1 = add(x, I);
    r2 = add(I, x);
    REQUIRE(eq(*r1, *r2));

    r1 = mul(x, I);
    r2 = mul(mul(I, i2), x);
    r3 = mul(mul(I, i3), x);
    r2 = add(r1, r2);
    REQUIRE(eq(*r3, *r2));

    r1 = real_double(0.1);
    r2 = Rational::from_mpq(mpq_class(1, 2));