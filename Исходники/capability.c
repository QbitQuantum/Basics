static TW_UINT16 get_default_paper_size(const supported_size_t *s, int n)
{
    DWORD paper;
    int rc;
    int defsize = -1;
    double width, height;
    int i;
    rc = GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_IPAPERSIZE | LOCALE_RETURN_NUMBER, (void *) &paper, sizeof(paper));
    if (rc > 0)
        switch (paper)
        {
            case 1:
                defsize = TWSS_USLETTER;
                break;
            case 5:
                defsize = TWSS_USLEGAL;
                break;
            case 8:
                defsize = TWSS_A3;
                break;
            case 9:
                defsize = TWSS_A4;
                break;
        }

    if (defsize == -1)
        return TWSS_NONE;

    if (get_width_height(&width, &height, TRUE) != TWCC_SUCCESS)
        return TWSS_NONE;

    for (i = 0; i < n; i++)
        if (s[i].size == defsize)
        {
            /* Sane's use of integers to store floats is a hair lossy; deal with it */
            if (s[i].x > (width + .01) || s[i].y > (height + 0.01))
                return TWSS_NONE;
            else
                return s[i].size;
        }

    return TWSS_NONE;
}