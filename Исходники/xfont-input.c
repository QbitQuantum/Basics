void DrawCharacters(Page *page)
{
    size_t start = page->start;
    size_t i;
    for (i = start; i < page->end; i++) {
        short x = character_positions[i].x;
        short y = character_positions[i].y;

        if (IsPrint(text[i])) {
draw:
            ;
            XChar2b font_code;
            XFontStruct *font = SelectFont(text[i], &font_code);
            GC gc = XCreateGC(disp, back_buffer, 0, NULL);
            XCopyGC(disp, default_gc, GCForeground | GCBackground, gc);
            XSetFont(disp, gc, font->fid);
            XDrawString16(disp, back_buffer, gc,
                          x, y + (font->ascent - default_font->ascent), &font_code, 1);
            XFreeGC(disp, gc);
        } else {
            if (EqAscii2b(text[i], '\n')) {
                // DOWNWARDS ARROW WITH TIP LEFTWARDS
                XChar2b symbol = { .byte1 = 0x21, .byte2 = 0xb2 };
                XDrawString16(disp, back_buffer, control_gc,
                              x, y,
                              &symbol, 1);
            } else if (EqAscii2b(text[i], '\t')) {
                ;
            } else {
                goto draw;
            }
        }
    }