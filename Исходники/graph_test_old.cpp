void test_rat2( void )
{
    NUPrecRational x1(10.0), y1(10.0), x2(20.0), y2(20.0), y(15.0), c;
    double n,d;

    c = x1 + (y-y1)*(x2-x1)/(y2-y1);
    c.Dump(&n,&d);
    printf( "%f/%f\n", n, d );
}