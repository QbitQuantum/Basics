using SymEngine::Subs;
using SymEngine::Derivative;
using SymEngine::function_symbol;
using SymEngine::I;
using SymEngine::real_double;
using SymEngine::complex_double;

TEST_CASE("test_printing(): printing", "[printing]")
{
    RCP<const Basic> r, r1, r2;
    RCP<const Integer> i = integer(-1);
    RCP<const Symbol> x  = symbol("x");
    RCP<const Symbol> y  = symbol("y");
    RCP<const Symbol> z  = symbol("z");

    r = div(integer(12), pow(integer(196), div(integer(1), integer(2))));
    REQUIRE(r->__str__() == "(3/49)*196**(1/2)");

    r = mul(integer(12), pow(integer(196), div(integer(1), integer(2))));
    REQUIRE(r->__str__() == "12*196**(1/2)");

    r = mul(integer(23), mul(pow(integer(5), div(integer(1), integer(2))),
        pow(integer(7), div(integer(1), integer(2)))));
    REQUIRE(r->__str__() == "23*5**(1/2)*7**(1/2)");

    r = mul(integer(2), pow(symbol("x"), integer(2)));
    REQUIRE(r->__str__() == "2*x**2");

    r = mul(integer(23), mul(pow(div(integer(5), integer(2)), div(integer(1), integer(2))),
        pow(div(integer(7), integer(3)), div(integer(1), integer(2)))));
    REQUIRE(r->__str__() == "23*(7/3)**(1/2)*(5/2)**(1/2)");