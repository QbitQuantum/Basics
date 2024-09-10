// 次のページの開始位置、あるいは文書の終端 (== text_length) を返す。
size_t FillPage(size_t start, Page *page, bool draw)
{
    XWindowAttributes attrs;
    XGetWindowAttributes(disp, win, &attrs);

    // ページのサイズ。
    const int LEFT_MARGIN	= 50;
    const int RIGHT_MARGIN	= attrs.width - LEFT_MARGIN;
    const int TOP_MARGIN	= 50;
    const int BOTTOM_MARGIN	= attrs.height - TOP_MARGIN;

    const XChar2b sp = { 0x00, 0x21 };
    const int EM = GetCharWidth(sp);

    // 行の高さ。
    const int LINE_HEIGHT = 22;

    // 現在の文字の描画位置。
    int x = LEFT_MARGIN, y = TOP_MARGIN + font->ascent;

    size_t i;
    for (i = start; i < text_length; i++) {
	// カーソルの描画
	if (draw && i == cursor_position) {
	    XFillRectangle(disp, win, cursor_gc,
			   x, y - font->ascent,
			   CURSOR_WIDTH, font->ascent + font->descent);
	}

	if (IsPrint(text[i])) {
	    // 印字可能文字の場合。

	    int width = GetCharWidth(text[i]);

	    // この文字を描画すると右マージンにかかるようなら改行する。
	    // ただし、行頭に居る場合は改行しない。
	    if ( x + width > RIGHT_MARGIN &&
		 !ForbiddenAtStart(text[i]) && // 行頭禁止文字ならばぶらさげる
		 x != LEFT_MARGIN ) {
		y += LINE_HEIGHT;
		x = LEFT_MARGIN;

		// ページにも収まらない場合、この位置で終了する。
		if (y + font->descent > BOTTOM_MARGIN) {
		    page->start = start;
		    page->end = i;
		    return i;
		}
	    }

	    if (draw) XDrawString16(disp, win, gc,
				    x, y,
				    &text[i], 1);
	    x += width;
	} else {
	    // ラインフィードで改行する。
	    if (EqAscii2b(text[i], '\n')) {
		if (draw) {
		    // DOWNWARDS ARROW WITH TIP LEFTWARDS
		    XChar2b symbol = { .byte1 = 0x21, .byte2 = 0xb2 };
		    XDrawString16(disp, win, control_gc,
				  x, y,
				  &symbol, 1);
		}
		y += LINE_HEIGHT;
		x = LEFT_MARGIN;

		// ページにも収まらない場合、次の位置で終了する。
		// ページ区切り位置での改行は持ち越さない。
		if (y + font->descent > BOTTOM_MARGIN) {
		    page->start = start;
		    page->end = i + 1;
		    return i + 1;
		}
	    } else if (EqAscii2b(text[i], '\t')) {
		int tab = EM * 8;
		x = LEFT_MARGIN + (((x - LEFT_MARGIN) / tab) + 1) * tab;
	    }
	}
    }
    if (draw && i == cursor_position) {
	XFillRectangle(disp, win, cursor_gc,
		       x, y - font->ascent,
		       CURSOR_WIDTH, font->ascent + font->descent);
    }
    if (draw) XDrawString(disp, win, control_gc,
			  x, y,
			  "[EOF]", 5);
    // 全てのテキストを配置した。
    page->start = start;
    page->end = text_length;
    return text_length;
}