void TextDisplay::RemoveStyle (int l1, int i1, int l2, int i2, int style) {
    for (int l = l1; l <= l2; ++l) {
        int first = (l == l1) ? i1 : -10000;
        int last = (l == l2) ? i2 : 10000;
        Line(l, true)->RemoveStyle(this, l, first, last, style);
    }
    if (l1 <= caretline && l2 >= caretline) {
        ShowCaret();
    }
}