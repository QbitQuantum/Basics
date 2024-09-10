/**
   Convert utf-8 string to wide string
 */
static wchar_t *utf2wcs(const char *in)
{
    iconv_t cd=(iconv_t) -1;
    int i,j;

    wchar_t *out;

    /*
      Try to convert to wchar_t. If that is not a valid character set,
      try various names for ucs-4. We can't be sure that ucs-4 is
      really the character set used by wchar_t, but it is the best
      assumption we can make.
    */
    const char **to_name=0;

    switch (sizeof(wchar_t))
    {

        case 2:
            to_name = iconv_wide_names_2;
            break;

        case 4:
            to_name = iconv_wide_names_4;
            break;

        default:
            to_name = iconv_wide_names_unknown;
            break;
    }


    /*
      The line protocol fish uses is always utf-8.
    */
    const char **from_name = iconv_utf8_names;

    size_t in_len = strlen(in);
    size_t out_len =  sizeof(wchar_t)*(in_len+2);
    size_t nconv;
    char *nout;

    out = (wchar_t *)malloc(out_len);
    nout = (char *)out;

    if (!out)
        return 0;

    for (i=0; to_name[i]; i++)
    {
        for (j=0; from_name[j]; j++)
        {
            cd = iconv_open(to_name[i], from_name[j]);

            if (cd != (iconv_t) -1)
            {
                goto start_conversion;

            }
        }
    }

start_conversion:

    if (cd == (iconv_t) -1)
    {
        /* Something went wrong.  */
        debug(0, L"Could not perform utf-8 conversion");
        if (errno != EINVAL)
            wperror(L"iconv_open");

        /* Terminate the output string.  */
        free(out);
        return 0;
    }

    /* FreeBSD has this prototype: size_t iconv (iconv_t, const char **...)
       OS X and Linux this one: size_t iconv (iconv_t, char **...)
       AFAIK there's no single type that can be passed as both char ** and const char **.
       Hence this hack.
    */
    nconv = hack_iconv(cd, &in, &in_len, &nout, &out_len);

    if (nconv == (size_t) -1)
    {
        debug(0, L"Error while converting from utf string");
        return 0;
    }

    *((wchar_t *) nout) = L'\0';

    /*
      Check for silly iconv behaviour inserting an bytemark in the output
      string.
     */
    if (*out == L'\xfeff' || *out == L'\xffef' || *out == L'\xefbbbf')
    {
        wchar_t *out_old = out;
        out = wcsdup(out+1);
        if (! out)
        {
            debug(0, L"FNORD!!!!");
            free(out_old);
            return 0;
        }
        free(out_old);
    }


    if (iconv_close(cd) != 0)
        wperror(L"iconv_close");

    return out;
}