int
first_one1( unsigned int u1 )
{
    unsigned long index;

    _BitScanReverse( &index, u1 );
    return 53 - index;
}