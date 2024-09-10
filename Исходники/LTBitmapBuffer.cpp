CBitmap* LTBitmapBuffer::GetBitmapCopy()
{
	CDC dc;
	dc.CreateCompatibleDC(p_DC);
	CBitmap* pbmpNew = new CBitmap;
	pbmpNew->CreateCompatibleBitmap(p_DC, Width(), Height());
	CBitmap* pbmpOld = dc.SelectObject(pbmpNew);

	dc.BitBlt(0, 0, Width(), Height(), p_DC, 0, 0, SRCCOPY);
	dc.SelectObject(pbmpOld);
	dc.DeleteDC();

	return pbmpNew;
}