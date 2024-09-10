void dropdown_draw(DROPDOWN *b, int x, int y, int width, int height)
{
    if(!b->open) {
        framerect(x, y, x + width, y + height, (b->mouseover ? C_GRAY2 : C_GRAY));
        drawrect(x + 1, y + 1, x + width - 1, y + height - 1, WHITE);

        if(b->dropcount) {
            setfont(FONT_TEXT);
            setcolor(COLOR_TEXT);
            STRING* e = b->ondisplay(b->selected, b);
            drawtextwidth(x + 2 * SCALE, width - 4 * SCALE, y + 2 * SCALE, e->str, e->length);
        }
    } else {
        active_x = x;
        active_y = y;
        active_width = width;
        active_height = height;
    }
}