/*
 * returns 1 if a character before s2 in s1 is single-byte,
 * returns 0 if it is multi-byte.
 */
int
_is_previous_single(
        char *s1,
        char *s2)
{
    int n = 1;

    if(MB_CUR_MAX == 1)
        return(1);

    while(*s1) {
        if(s1 == s2) {
            if(n > 1)
                return(0);
            else
                return(1);
        }
        n = mblen(s1, MB_CUR_MAX) > 1 ? mblen(s1, MB_CUR_MAX) : 1;
        s1 += n;
    }
    return(1);
}