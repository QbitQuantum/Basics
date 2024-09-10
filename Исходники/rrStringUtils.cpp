string dblToStr(const double& nt)
{
    char str[25];
    int sig = 5; /* significant digits */
    char* ptr =  gcvt(nt, sig, str);
    return string(str);
}