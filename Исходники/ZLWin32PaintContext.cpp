int ZLWin32PaintContext::stringWidth(const char *str, int len, bool rtl) const {
	if (myDisplayContext == 0) {
		return 0;
	}
	SetTextAlign(myDisplayContext, rtl ? TA_RTLREADING : 0);
	SIZE size;
	int utf8len = ZLUnicodeUtil::utf8Length(str, len);
	if (utf8len == len) {
		GetTextExtentPointA(myDisplayContext, str, len, &size);
	} else {
		static ZLUnicodeUtil::Ucs2String ucs2Str;
		ucs2Str.clear();
		ZLUnicodeUtil::utf8ToUcs2(ucs2Str, str, len, utf8len);
		GetTextExtentPointW(myDisplayContext, ::wchar(ucs2Str), utf8len, &size);
	}
	return size.cx;
}