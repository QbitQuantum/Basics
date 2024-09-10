static inline void WCEL_Update(WCEL_Context* ctx, int beg, int len)
{
    int         i, last;
    DWORD       count;
    WCHAR       tmp[2];

    /* bare console case is handled in CONSOLE_ReadLine (we always reprint the whole string) */
    if (!ctx->shall_echo || !ctx->can_pos_cursor) return;

    for (i = last = beg; i < beg + len; i++)
    {
        if (ctx->line[i] < ' ')
        {
            if (last != i)
            {
                WriteConsoleOutputCharacterW(ctx->hConOut, &ctx->line[last], i - last,
                                             WCEL_GetCoord(ctx, last), &count);
                FillConsoleOutputAttribute(ctx->hConOut, ctx->csbi.wAttributes, i - last,
                                           WCEL_GetCoord(ctx, last), &count);
            }
            tmp[0] = '^';
            tmp[1] = '@' + ctx->line[i];
            WriteConsoleOutputCharacterW(ctx->hConOut, tmp, 2,
                                         WCEL_GetCoord(ctx, i), &count);
            FillConsoleOutputAttribute(ctx->hConOut, ctx->csbi.wAttributes, 2,
                                       WCEL_GetCoord(ctx, i), &count);
            last = i + 1;
        }
    }
    if (last != beg + len)
    {
        WriteConsoleOutputCharacterW(ctx->hConOut, &ctx->line[last], i - last,
                                     WCEL_GetCoord(ctx, last), &count);
        FillConsoleOutputAttribute(ctx->hConOut, ctx->csbi.wAttributes, i - last,
                                   WCEL_GetCoord(ctx, last), &count);
    }
}