using SymEngine::LambdaComplexDoubleVisitor;
using SymEngine::max;
using SymEngine::E;
using SymEngine::gamma;
using SymEngine::loggamma;
using SymEngine::min;

TEST_CASE("Evaluate to double", "[lambda_double]")
{
    RCP<const Basic> x, y, z, r;
    double d;
    x = symbol("x");
    y = symbol("y");
    z = symbol("z");

    r = add(x, add(mul(y, z), pow(x, integer(2))));

    LambdaRealDoubleVisitor v;
    v.init({x, y, z}, *r);

    d = v.call({1.5, 2.0, 3.0});
    REQUIRE(::fabs(d - 9.75) < 1e-12);

    d = v.call({1.5, -1.0, 2.0});
    REQUIRE(::fabs(d - 1.75) < 1e-12);

    r = max({x, add(mul(y, z), integer(3))});
    v.init({x, y, z}, *r);

    d = v.call({4.0, 1.0, 2.5});
    REQUIRE(::fabs(d - 5.5) < 1e-12);