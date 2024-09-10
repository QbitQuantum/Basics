/* Transform ASCII chars in string to upper case */
tmbstr tmbstrtoupper(tmbstr s)
{
    tmbstr cp;

    for (cp = s; *cp; ++cp)
        *cp = (tmbchar)ToUpper(*cp);

    return s;
}