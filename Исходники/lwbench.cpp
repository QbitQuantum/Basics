double E()
{
    RCP<const Basic> s = integer(0);
    RCP<const Basic> y = symbol("y");
    RCP<const Basic> t = symbol("t");

    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= 10; i++) {
        s = add(s, div(mul(integer(i), mul(y, pow(t, integer(i)))),
                    pow(add(y, mul(integer(abs(5 - i)), t)), integer(i))));
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count()/1000000000.0;
}