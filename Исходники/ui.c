static int ui_draw_chars(char *chars, int x, int y, uint16_t fg, uint16_t bg) {
    int width = tb_width();
    int pointer = 0;
    int counter = 0;
    int length;
    mbstate_t state;
    wchar_t ch;

    // Initialize multi-byte state
    mbrlen(NULL, 0, &state);

    while (chars[pointer] != '\0') {
        length = mbrtowc(&ch, chars + pointer, 4, &state);

        tb_change_cell(x + pointer, y, ch, fg, bg);
        pointer += length;
        counter++;
    }

    // Draw spaces for the remaining of the line
    for (int i = counter; i < width; i++) {
        tb_change_cell(x + i, y, ' ', fg, bg);
    }

    return counter;
}