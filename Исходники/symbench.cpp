double S2()
{
    RCP<const Basic> x = symbol("x");
    RCP<const Basic> y = symbol("y");
    RCP<const Basic> z = symbol("z");
    RCP<const Basic> e;
    RCP<const Basic> f;

    e = pow(add(pow(x, sin(x)), add(pow(y, cos(y)), pow(z, add(x, y)))), integer(100));

    auto t1 = std::chrono::high_resolution_clock::now();
    f = expand(e);
    auto t2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count()/1000000000.0;
}