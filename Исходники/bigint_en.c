int main()
{
    // printf("hello, world");

    char result[BUFFER_SIZE];
    char remainder[BUFFER_SIZE];

    // please make sure the bit length is enough before calculate
    // especially when you do a large power operation
    // you can change it by define: BIG_INT_BIT_LEN
    // the default bit length for BigInt is 1024

    // routine test
    puts(Add("2010", "4", result));
    puts(Sub("0", "2014", result));
    puts(Mul("2", "43", result));
    puts(Div("86", "10", result, remainder));
    puts(remainder);
    puts(Mod("-86", "10", result));
    puts(PowMod("7", "80", "86", result));

    // BigInt test
    puts(Sub("233333333333333333333333333333333333333333333333", "33", result));
    puts(Mul("2333333333333333333333333333333", "2333333333333333333", result));
    puts(Div("2333333333333333333333333333333", "2333333333333333332", result, remainder));
    puts(remainder);
    puts(Pow("8", "86", result));

    return 0;
}