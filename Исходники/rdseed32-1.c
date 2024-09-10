void extern
rdseed_test (unsigned int *p)
{
    volatile int r;
    r = _rdseed32_step (p);
}