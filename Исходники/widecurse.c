static int putxy(WINDOW *win, int width, int *i, int *y, int *x, char *str)
{
    if ((unsigned char) str[0] > 0x7F) {
        wchar_t dest[2];
        int bytes = mbtowc(dest, &str[0], 3) - 1;

        if (bytes >= 0) {
            /* To deal with non-latin characters that can take
               up more than one character's alotted width, 
               with offset x by wcwidth(character) rather than 1 */

            /* Took me forever to find that function, thanks
               Andreas (newsbeuter) for that one. */

            int rwidth = wcwidth(dest[0]);
            if (rwidth < 0)
                rwidth = 1;
            if (rwidth > (width - *x))
                return 1;

            dest[1] = 0;
            mvwaddwstr(win, *y, *x, dest);
            *x += rwidth;
            *i += bytes;
        }
    } else
        mvwaddch(win, *y, (*x)++, str[0]);

    return 0;
}