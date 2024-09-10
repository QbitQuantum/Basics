int PDC_resize_screen(int nlines, int ncols)
{
    SMALL_RECT rect;
    COORD size, max;

    bool prog_resize = nlines || ncols;

    if (!prog_resize)
    {
        nlines = PDC_get_rows();
        ncols = PDC_get_columns();
    }

    if (nlines < 2 || ncols < 2)
        return ERR;

    max = GetLargestConsoleWindowSize(pdc_con_out);

    rect.Left = rect.Top = 0;
    rect.Right = ncols - 1;

    if (rect.Right > max.X)
        rect.Right = max.X;

    rect.Bottom = nlines - 1;

    if (rect.Bottom > max.Y)
        rect.Bottom = max.Y;

    size.X = rect.Right + 1;
    size.Y = rect.Bottom + 1;

    _fit_console_window(pdc_con_out, &rect);
    SetConsoleScreenBufferSize(pdc_con_out, size);

    if (prog_resize)
    {
        _fit_console_window(pdc_con_out, &rect);
        SetConsoleScreenBufferSize(pdc_con_out, size);
    }
    SetConsoleActiveScreenBuffer(pdc_con_out);

    PDC_flushinp();

    SP->resized = FALSE;
    SP->cursrow = SP->curscol = 0;

    return OK;
}