extern int testremainder(void)
{
    static double s_rd1 = 2.5;
    static double s_rd2 = 2.0;
    static double s_rd3 = 0.5;
    return remainder(s_rd1, s_rd2) == s_rd3;
}