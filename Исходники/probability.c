static int pavg_skip(unsigned char *s, int type)
{
    unsigned char c1, c2, lc1, lc2;
    int count = 0;
    int total = 0;

    if (pfoldedsets & type)
    {
        while(*s)
        {
            c1 = *s++;

            if (!(pcharset[c1] & type))
                continue;

            for (c2 = *s; c2; c2 = *++s)
                if (pcharset[c2] & type)
                    break;

            if (!c2)
                break;

            lc1 = ToLower(c1) - PMINCHAR;
            lc2 = ToLower(c2) - PMINCHAR;
            c1 = ToUpper(c1) - PMINCHAR;
            c2 = ToUpper(c2) - PMINCHAR;

            count++;
            total += probabilities[c1][c2];
            if (lc1 != c1)
            {
                total += probabilities[lc1][c2];
                if (lc2 != c2)
                    total += probabilities[lc1][lc2];
            }
            if (lc2 != c2)
                total += probabilities[c1][lc2];
        }
    }
    else
    {
        while (*s)
        {
            c1 = *s++;

            if (!(pcharset[c1] & type))
                continue;

            for (c2 = *s; c2; c2 = *++s)
                if (pcharset[c2] & type)
                    break;

            if (!c2)
                break;

            c1 -= PMINCHAR;
            c2 -= PMINCHAR;
            total += probabilities[c1][c2];
            count++;
        }
    }

    if (!count)
        return -1;

    return (total/count);
}