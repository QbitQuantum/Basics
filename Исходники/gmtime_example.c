int main(void)
{
    struct tm ptm;
    time_t t = time(NULL);
    ptm = *gmtime(&t);
    printf("UTC:   %s", asctime(&ptm));
    ptm = *localtime(&t);
    printf("local: %s", asctime(&ptm));

#ifdef __STDC_LIB_EXT1__
    struct tm buf;
    char str[26];
    asctime_s(str, sizeof str, gmtime_s(&t, &buf));
    printf("UTC:   %s", str);
    asctime_s(str, sizeof str, localtime_s(&t, &buf));
    printf("local: %s", str);
#endif
}