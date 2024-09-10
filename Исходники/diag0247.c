test_one()
{
    X1 x1(1);
    Y1 y1(1);

    f1( x1, y1 ); // in fact, it should find ambiguity, not pass this
}