// wchar_t version.
wchar_t *my_strrchrW(wchar_t *string, const wchar_t c)
{
    wchar_t  sch;
    wchar_t* rval = NULL;

    while ((sch = *string) != L'\0')
    {
        if (sch == c)
        {
            rval = string;
            break;
        }
        string = CharNextW(string);
    }

    return rval;
}