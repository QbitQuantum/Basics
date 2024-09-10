int
sc_main( int argc, char* argv[] )
{
    signed int vali[5] = { 0, 1, (unsigned)-1, 7, (unsigned)-8 };
    signed int valj[5] = { 0, 1, (unsigned)-1, 7, (unsigned)-8 };

    for (int i = 3; i < 32; ++i) {
        for (int j = 3; j < 32; ++j) {
            cout << "i = " << i << ", j = " << j << endl;

            sc_unsigned x(i);
            sc_unsigned y(j);
            sc_unsigned z(64);

            vali[3] = (1 << (i - 1)) - 1;
            vali[4] = - (1 << (i - 1));

            valj[3] = (1 << (j - 1)) - 1;
            valj[4] = - (1 << (j - 1));

            for (int ii = 0; ii < 100; ++ii) {
                for (int jj = 0; jj < 100; ++jj) {
                    unsigned qi = (ii < 5) ? vali[ii] : (rng.rand() & ((1 << i) - 1));
                    unsigned qj = (jj < 5) ? valj[jj] : (rng.rand() & ((1 << j) - 1));

                    if (qi & (1 << (i - 1))) {
                        qi = (qi << (32 - i)) >> (32 - i);
                    }
                    if (qj & (1 << (j - 1))) {
                        qj = (qj << (32 - j)) >> (32 - j);
                    }

                    x = qi;
                    TEST(x,qi );
                    y = qj;
                    TEST(y,qj );
                    TEST((x == qj),(qi == qj));
                    TEST((x == qj),(qj == x));
                    TEST((x != qj),(qi != qj));
                    TEST((x != qj),(qj != x));
                    TEST((x < qj),(qi < qj));
                    TEST((x < qj),(qj > x));
                    TEST((x <= qj),(qi <= qj));
                    TEST((x <= qj),(qj >= x));
                    TEST((x > qj),(qi > qj));
                    TEST((x > qj),(qj < x));
                    TEST((x >= qj),(qi >= qj));
                    TEST((x >= qj),(qj <= x));
                    z = x + qj;
                    TEST((sc_unsigned)( z.range(31,0) ), (qi + qj) );
                    z = qi + y;
                    TEST((sc_unsigned)( z.range(31,0) ), (qi + qj) );
                    z = x - qj;
                    TEST((sc_unsigned)( z.range(31,0) ), (qi - qj) );
                    z = qi - y;
                    TEST((sc_unsigned)( z.range(31,0) ), (qi - qj) );
                    z = x * qj;
                    TEST((sc_unsigned)( z.range(31,0) ), (qi * qj) );
                    z = qi * y;
                    TEST((sc_unsigned)( z.range(31,0) ), (qi * qj) );
                    if (qj != 0) {
                        z = x / qj;
                        TEST((sc_unsigned)( z.range(31,0) ),(qi/qj));
                        z = qi / y;
                        TEST((sc_unsigned)( z.range(31,0) ),(qi/qj));
                        z = x % qj;
                        TEST((sc_unsigned)( z.range(31,0) ),(qi%qj));
                        z = qi % y;
                        TEST((sc_unsigned)( z.range(31,0) ),(qi%qj));
                    }
                    z = x & qj;
                    TEST((sc_unsigned)( z.range(31,0) ), (qi & qj) );
                    z = qi & y;
                    TEST((sc_unsigned)( z.range(31,0) ), (qi & qj) );
                    z = x | qj;
                    TEST((sc_unsigned)( z.range(31,0) ), (qi | qj) );
                    z = qi | y;
                    TEST((sc_unsigned)( z.range(31,0) ), (qi | qj) );
                    z = x ^ qj;
                    TEST((sc_unsigned)( z.range(31,0) ), (qi ^ qj) );
                    z = qi ^ y;
                    TEST((sc_unsigned)( z.range(31,0) ), (qi ^ qj) );
                }
            }
        }