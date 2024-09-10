wchar_t *parse_util_unescape_wildcards(const wchar_t *str)
{
    wchar_t *in, *out;
    wchar_t *unescaped;

    CHECK(str, 0);

    unescaped = wcsdup(str);

    if (!unescaped)
    {
        DIE_MEM();
    }

    for (in=out=unescaped; *in; in++)
    {
        switch (*in)
        {
            case L'\\':
            {
                switch (*(in + 1))
                {
                    case L'*':
                    case L'?':
                    {
                        in++;
                        *(out++)=*in;
                        break;
                    }
                    case L'\\':
                    {
                        in++;
                        *(out++)=L'\\';
                        *(out++)=L'\\';
                        break;
                    }
                    default:
                    {
                        *(out++)=*in;
                        break;
                    }
                }
                break;
            }

            case L'*':
            {
                *(out++)=ANY_STRING;
                break;
            }

            case L'?':
            {
                *(out++)=ANY_CHAR;
                break;
            }

            default:
            {
                *(out++)=*in;
                break;
            }
        }
    }
    *out = *in;
    return unescaped;
}