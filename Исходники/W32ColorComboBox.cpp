void W32ColorComboBox::drawItemCallback(DRAWITEMSTRUCT &di) {
	RECT rectangle;
	rectangle.top = di.rcItem.top + 1;
	rectangle.bottom = di.rcItem.bottom - 2;
	rectangle.left = di.rcItem.left + 2;
	rectangle.right = rectangle.left + 3 * (myPixelHeight - 4) / 2;
	MoveToEx(di.hDC, rectangle.left, rectangle.top, 0);
	LineTo(di.hDC, rectangle.left, rectangle.bottom);
	LineTo(di.hDC, rectangle.right, rectangle.bottom);
	LineTo(di.hDC, rectangle.right, rectangle.top);
	LineTo(di.hDC, rectangle.left, rectangle.top);
	++rectangle.top;
	++rectangle.left;
	ZLColor color = this->color(di.itemID);
	HBRUSH brush = CreateSolidBrush(RGB(color.Red, color.Green, color.Blue));
	FillRect(di.hDC, &rectangle, brush);
	DeleteObject(brush);

	TEXTMETRIC tm;
	const ZLUnicodeUtil::Ucs2String &txt = text(di.itemID);
	GetTextMetrics(di.hDC, &tm);
	if (!txt.empty()) {
		TextOutW(di.hDC, rectangle.right + 8, (rectangle.top + rectangle.bottom - tm.tmHeight) / 2, ::wchar(txt), txt.size() - 1);
	} else {
		std::string colorString = "(";
		ZLStringUtil::appendNumber(colorString, color.Red);
		colorString += ",";
		ZLStringUtil::appendNumber(colorString, color.Green);
		colorString += ",";
		ZLStringUtil::appendNumber(colorString, color.Blue);
		colorString += ")";
		TextOutA(di.hDC, rectangle.right + 8, (rectangle.top + rectangle.bottom - tm.tmHeight) / 2, colorString.data(), colorString.length());
	}
}