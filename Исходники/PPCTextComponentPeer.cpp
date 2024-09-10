static long getWin32SelPos(AwtTextComponent *c, long orgPos)
{
    long mblen;
    long pos = 0;
    long cur = 0;
    TCHAR *mbbuf;

    if ((mblen = c->GetTextLength()) == 0)
       return 0;
    mbbuf = new TCHAR[mblen + 1];
    c->GetText(mbbuf, mblen + 1);

    while (cur < orgPos && pos < mblen) {
#ifndef UNICODE
       if (IsDBCSLeadByte(mbbuf[pos])) {
	      pos++;
       } else if (mbbuf[pos] == '\r' && mbbuf[pos + 1] == '\n') {
	   pos++;
       }
#else
       if (mbbuf[pos] == TEXT('\r') && mbbuf[pos + 1] == TEXT('\n')) {
	   pos++;
       }
#endif
       pos++;
       cur++;
    }
    delete[] mbbuf;
    return pos;
}