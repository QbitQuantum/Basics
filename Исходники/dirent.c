//
// Do a DOS-style wildcard pattern match.
//
static BOOL _DosPatternMatch(LPCSTR szPattern, LPCSTR szFile)
{
	register LPCSTR p, q;
	unsigned int mbc;

	p = szPattern;
	q = szFile;
	for (;;) {
	  //
	  // DOC BUG: _mbsnextc() returns the _current_ multi-byte char
	  //
	  switch (mbc = _mbsnextc(p), p = _mbsinc(p), mbc) {
		case '\0':
			goto done;
		case '?':
			if (*q == '\0')
				return FALSE;
			q = _mbsinc(q);
			break;
		case '*':
			//
			// DOC BUG: _mbsnextc() returns the _current_ multi-byte char
			//
			mbc = _mbsnextc(p);
			if (mbc != '?' && mbc != '*') {
				mbc = _mbctolower(mbc);
				while (_mbctolower(*q) != mbc) {
					if (*q == '\0') {
						return mbc == '\0' ? TRUE : FALSE;
					}
					q = _mbsinc(q);
				}
			}
			do {
				if (_DosPatternMatch(p, q)) // recurse
					return TRUE;
				mbc = _mbsnextc(q); // current char, not "next"
				q = _mbsinc(q);
			} while (mbc != '\0');
			return FALSE;
	    default:
			if (_mbctolower(*q) != _mbctolower(mbc)) {
				return FALSE;
			}
			q = _mbsinc(q);
			break;
	  }
	}
done:
	return (*q == '\0') ? TRUE : FALSE;
}