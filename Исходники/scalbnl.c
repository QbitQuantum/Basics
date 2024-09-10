long double scalbnl(long double x, int exp)
{
#if defined(__arm__) || defined(_ARM_)
    return scalbn(x, exp);
#else
#error Not supported on your platform yet
#endif
}