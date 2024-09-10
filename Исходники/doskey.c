//------------------------------------------------------------------------------
int begin_doskey(wchar_t* chars, unsigned max_chars)
{
    // Find the alias for which to retrieve text for.
    wchar_t alias[64];
    {
        int i, n;
        int found_word = 0;
        const wchar_t* read = chars;
        for (i = 0, n = min(sizeof_array(alias) - 1, max_chars); i < n && *read; ++i)
        {
            if (!!iswspace(*read) == found_word)
            {
                if (!found_word)
                    found_word = 1;
                else
                    break;
            }

            alias[i] = *read++;
        }

        alias[i] = '\0';
    }

    // Find the alias' text.
    {
        int bytes;
        wchar_t* exe;
        wchar_t exe_path[MAX_PATH];

        GetModuleFileNameW(NULL, exe_path, sizeof_array(exe_path));
        exe = wcsrchr(exe_path, L'\\');
        exe = (exe != NULL) ? (exe + 1) : exe_path;

        // Check it exists.
        if (!GetConsoleAliasW(alias, exe_path, 1, exe))
            return 0;

        // It does. Allocate space and fetch it.
        bytes = max_chars * sizeof(wchar_t);
        g_state.alias_text = malloc(bytes * 2);
        GetConsoleAliasW(alias, g_state.alias_text, bytes, exe);

        // Copy the input and tokenise it. Lots of pointer aliasing here...
        g_state.input = g_state.alias_text + max_chars;
        memcpy(g_state.input, chars, bytes);

        g_state.token_count = tokenise(g_state.input, g_state.tokens,
                                       sizeof_array(g_state.tokens));

        g_state.alias_next = g_state.alias_text;
    }

    // Expand all '$?' codes except those that expand into arguments.
    {
        wchar_t* read = g_state.alias_text;
        wchar_t* write = read;
        while (*read)
        {
            if (read[0] != '$')
            {
                *write++ = *read++;
                continue;
            }

            ++read;
            switch (*read)
            {
            case '$':
                *write++ = '$';
                break;
            case 'g':
            case 'G':
                *write++ = '>';
                break;
            case 'l':
            case 'L':
                *write++ = '<';
                break;
            case 'b':
            case 'B':
                *write++ = '|';
                break;
            case 't':
            case 'T':
                *write++ = '\1';
                break;

            default:
                *write++ = '$';
                *write++ = *read;
            }

            ++read;
        }

        *write = '\0';
    }

    return continue_doskey(chars, max_chars);
}