static void getCursorRect(struct OzUITextEdit *textEdit, struct Rect *cursorRect)
{
    copyRect(cursorRect, &textEdit->layout->charLayout[textEdit->cursorPos].rect);
    cursorRect->w = textEdit->fontSize/2;
}