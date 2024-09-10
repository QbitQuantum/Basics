int main( void )
{
    mbstate_t mbs;
    memset(&mbs, 0, sizeof mbs);

    TESTCASE(mbsinit(NULL) != 0);
    TESTCASE(mbsinit(&mbs) != 0);

#ifndef REGTEST
    // Surrogate pending
    mbs._Surrogate = 0xFEED;
    TESTCASE(mbsinit(&mbs) == 0);

    mbs._Surrogate = 0;
    mbs._PendState = 1;
    TESTCASE(mbsinit(&mbs) == 0);
#endif
    return TEST_RESULTS;
}