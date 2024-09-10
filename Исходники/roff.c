int main()
{

    TXTLEN = o_pl-o_m1-o_m2-o_m3-o_m4 - 2;
    assylen = 0;
    assyline[0] = 0;
    readfile();

    writebreak();
    endpage();
#ifdef H_LANG
    exit();
#else
    exit(0);
#endif
}