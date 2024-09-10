    REQUIRE(unified_eq(gens, rgens));

    // 2**(2*x + 1) -> (2**x)
    basic = pow(i2, add(mul(i2, x), one));
    gens = _find_gens_poly(basic);
    rgens = {{twopx, one}};
    REQUIRE(unified_eq(gens, rgens));

    // 2**(x**(x+1))-> (2**(x**(x+1)))
    basic = pow(i2, pow(x, add(x, one)));
    gens = _find_gens_poly(basic);
    rgens = {{basic, one}};
    REQUIRE(unified_eq(gens, rgens));

    // sin(x)*sin(y) + sin(x)**2 + sin(y) -> (sin(x), sin(y))
    basic = add(mul(sin(x), sin(y)), add(pow(sin(x), i2), sin(y)));
    gens = _find_gens_poly(basic);
    rgens = {{sin(x), one}, {sin(y), one}};
    REQUIRE(unified_eq(gens, rgens));

    // 2**x + 2**(x+y) -> (2**x, 2**y)
    basic = add(twopx, pow(i2, add(x, y)));
    gens = _find_gens_poly(basic);
    rgens = {{pow(i2, y), one}, {twopx, one}};
    REQUIRE(unified_eq(gens, rgens));

    // x**x + x**(x/2) + x**(x/3) -> (x**(x/6))
    basic = add(pow(x, x), add(pow(x, div(x, i2)), pow(x, div(x, i3))));
    gens = _find_gens_poly(basic);
    rgens = {{pow(x, x), rcp_static_cast<const Number>(div(one, i6))}};
    REQUIRE(unified_eq(gens, rgens));