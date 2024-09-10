/* We need to handle \ in paths which are to be passed to R code.
   Since these can include \\ for network drives, we cannot just use /,
   although we did prior to R 2.4.0.

   MBCS-aware since 2.4.0.
 */
static void double_backslashes(char *s, char *out)
{
    char *p = s;

    int i;
    if(mbcslocale) {
	mbstate_t mb_st; int used;
	mbs_init(&mb_st);
	while((used = Mbrtowc(NULL, p, MB_CUR_MAX, &mb_st))) {
	    if(*p == '\\') *out++ = '\\';
	    for(i = 0; i < used; i++) *out++ = *p++;
	}
    } else
	for (; *p; p++)
	    if (*p == '\\') {*out++ = *p; *out++ = *p;} else *out++ = *p;
    *out = '\0';
}