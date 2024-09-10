int main(int argc, char **argv)
#endif
{
    PRTime ct;
    PRExplodedTime et;
    PRStatus rv;
    char *sp1 = "Sat, 1 Jan 3001 00:00:00";  /* no time zone */
    char *sp2 = "Fri, 31 Dec 3000 23:59:60";  /* no time zone, not normalized */

#if _MSC_VER >= 1400 && !defined(WINCE)
    /* Run this test in the US Pacific Time timezone. */
    _putenv_s("TZ", "PST8PDT");
    _tzset();
#endif

    rv = PR_ParseTimeString(sp1, PR_FALSE, &ct);
    printf("rv = %d\n", rv);
    PR_ExplodeTime(ct, PR_GMTParameters, &et);
    PrintExplodedTime(&et);
    printf("\n");

    rv = PR_ParseTimeString(sp2, PR_FALSE, &ct);
    printf("rv = %d\n", rv);
    PR_ExplodeTime(ct, PR_GMTParameters, &et);
    PrintExplodedTime(&et);
    printf("\n");

    return 0;
}