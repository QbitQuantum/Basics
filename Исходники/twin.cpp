UINT TWin::GetDlgItemTextU8(int ctlId, char *buf, int len)
{
	Wstr	wbuf(len);

	*buf = 0;
	GetDlgItemTextW(ctlId, wbuf.Buf(), len);

	return	WtoU8(wbuf.s(), buf, len);
}