//------------------------------------------------------------------------------
static int getc_impl(FILE* stream)
{
    int i;
    while (1)
    {
        wchar_t wc[2];
        char utf8[4];

        i = _getwch();
        if (i == 0)
        {
            i = 0xe0;
        }

        // treat esc like cmd.exe does - clear the line.
        if (i == 0x1b)
        {
            rl_delete_text(0, rl_end);
            rl_point = 0;
            display();
            continue;
        }

        if (i < 0x7f || i == 0xe0)
        {
            break;
        }

        // Convert to utf-8 and insert directly into rl's line buffer.
        wc[0] = (wchar_t)i;
        wc[1] = L'\0';

        WideCharToMultiByte(
            CP_UTF8, 0,
            wc, -1,
            utf8, sizeof(utf8),
            NULL,
            NULL
        );

        rl_insert_text(utf8);
        display();
    }

    // Set the "meta" key bit if the ALT key is pressed.
    if (GetAsyncKeyState(VK_MENU) & 0x8000)
    {
        i |= 0x80;
    }

    return i;
}