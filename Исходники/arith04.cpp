int
sc_main( int argc, char* argv[] )
{
    signed int vali[5] = { 0, 1, -1, 7, -8 };
    signed int valj[5] = { 0, 1, -1, 7, -8 };

    for (int i = 3; i < 32; ++i) {
        for (int j = 3; j < 32; ++j) {
            cout << "i = " << i << ", j = " << j << endl;

            sc_signed x(i);
            sc_signed y(j);
            sc_signed z(64);

            vali[3] = (1 << (i - 1)) - 1;
            vali[4] = - (1 << (i - 1));

            valj[3] = (1 << (j - 1)) - 1;
            valj[4] = - (1 << (j - 1));

            for (int ii = 0; ii < 100; ++ii) {
                for (int jj = 0; jj < 100; ++jj) {
                    signed int qi = (ii < 5) ? vali[ii] : (rng.rand() & ((1 << i) - 1));
                    signed int qj = (jj < 5) ? valj[jj] : (rng.rand() & ((1 << j) - 1));
                    signed int tqi;

                    if (qi & (1 << (i - 1))) {
                        qi = (qi << (32 - i)) >> (32 - i);
                    }
                    if (qj & (1 << (j - 1))) {
                        qj = (qj << (32 - j)) >> (32 - j);
                    }

                    x = qi;
                    tqi = qi;
                    assert( x == qi );
                    y = qj;
                    assert( y == qj );
                    assert((x == qj) == (qi == qj));
                    assert((x == qj) == (qj == x));
                    assert((x != qj) == (qi != qj));
                    assert((x != qj) == (qj != x));
                    assert((x < qj) == (qi < qj));
                    assert((x < qj) == (qj > x));
                    assert((x <= qj) == (qi <= qj));
                    assert((x <= qj) == (qj >= x));
                    assert((x > qj) == (qi > qj));
                    assert((x > qj) == (qj < x));
                    assert((x >= qj) == (qi >= qj));
                    assert((x >= qj) == (qj <= x));

                    x += y;
                    tqi += qj;
                    tqi = (tqi << (32 - i)) >> (32 - i);
                    assert( x == tqi );

                    x = qi;
                    tqi = qi;
                    x -= y;
                    tqi -= qj;
                    tqi = (tqi << (32 - i)) >> (32 - i);
                    assert( x == tqi );

                    x = qi;
                    tqi = qi;
                    x *= y;
                    tqi *= qj;
                    tqi = (tqi << (32 - i)) >> (32 - i);
                    assert( x == tqi );

                    if (y != 0) {
                        x = qi;
                        tqi = qi;
                        x /= y;
                        tqi /= qj;
                        tqi = (tqi << (32 - i)) >> (32 - i);
                        assert( x == tqi );

                        x = qi;
                        tqi = qi;
                        x %= y;
                        tqi %= qj;
                        tqi = (tqi << (32 - i)) >> (32 - i);
                        assert( x == tqi );
                    }

                    x = qi;
                    tqi = qi;
                    x &= y;
                    tqi &= qj;
                    tqi = (tqi << (32 - i)) >> (32 - i);
                    assert( x == tqi );

                    x = qi;
                    tqi = qi;
                    x |= y;
                    tqi |= qj;
                    tqi = (tqi << (32 - i)) >> (32 - i);
                    assert( x == tqi );

                    x = qi;
                    tqi = qi;
                    x ^= y;
                    tqi ^= qj;
                    tqi = (tqi << (32 - i)) >> (32 - i);
                    assert( x == tqi );

                    if (jj < i - 1) {
                        x = qi;
                        tqi = qi;
                        x <<= jj;
                        tqi <<= jj;
                        tqi = (tqi << (32 - i)) >> (32 - i);
                        assert( x == tqi );

                        x = qi;
                        tqi = qi;
                        x >>= jj;
                        tqi >>= jj;
                        tqi = (tqi << (32 - i)) >> (32 - i);
                        assert( x == tqi );
                    }
                }