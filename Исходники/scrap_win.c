int
scrap_get_types_win (char** types)
{
    UINT format = 0;
    char **tmptypes;
    int count = -1;
    int i, len, size;
    char tmp[100] = { '\0' };

    if (!OpenClipboard (_sdlwindow))
    {
        SDL_SetError ("could not access clipboard");
        return -1;
    }

    size = CountClipboardFormats ();
    if (size == 0)
    {
        CloseClipboard ();
        return 0; /* No clipboard data. */
    }

    for (i = 0; i < size; i++)
    {
        format = EnumClipboardFormats (format);
        if (format == 0)
        {
            /* Something wicked happened. */
            while (i > 0)
                free (types[i]);
            free (types);
            CloseClipboard ();
            SDL_SetError ("error on retrieving the formats");
            return -1;
        }

        /* No predefined name, get the (truncated) name. */
        len = _lookup_clipboard_format (format, tmp, 100);
        if (len == 0)
            continue;
        count++;

        tmptypes = realloc (types, sizeof (char *) * (count + 1));
        if (!tmptypes)
        {
            while (count > 0)
            {
                free (types[count]);
                count--;
            }
            free (types);
            CloseClipboard ();
            SDL_SetError ("could allocate memory");
            return -1;
        }
        types = tmptypes;
        types[count] = malloc (sizeof (char) * (len + 1));
        if (!types[count])
        {
            while (count > 0)
            {
                free (types[count]);
                count--;
            }
            free (types);
            CloseClipboard ();
            SDL_SetError ("could allocate memory");
            return -1;
        }

        memset (types[count], 0, len + 1);
        memcpy (types[count], tmp, len);
    }

    tmptypes = realloc (types, sizeof (char *) * (count + 1));
    if (!tmptypes)
    {
        while (count > 0)
        {
            free (types[count]);
            count--;
        }
        free (types);
        CloseClipboard ();
        SDL_SetError ("could allocate memory");
        return -1;
    }
    types = tmptypes;
    types[count] = NULL;
    CloseClipboard ();
    return 1;
}