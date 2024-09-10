	debuggeroutbuf<char>::int_type debuggeroutbuf<char>::overflow(int_type ch)
	{
		if(ch == traits_type::eof()) return traits_type::eof();
		*epptr() = ch;
		// SJIS?
		if(-1 == _ismbstrail((const unsigned char *)pbase(), (const unsigned char *)epptr())) {
			char *lbp;
			for(lbp = epptr()-1; lbp > pbase(); lbp--) {
				if(-1 == _ismbslead((const unsigned char *)pbase(), (const unsigned char *)lbp)) {
					break;
				}
			}
			int _ch = *lbp; *lbp = '\0';
			sync();
			sputc(_ch);
			for(lbp++; lbp <= epptr(); lbp++) {
				sputc(*lbp);
			}
			*epptr() = '\0';
		}
		else {
			*epptr() = '\0';
			sync();
			sputc(ch);
		}
		return traits_type::not_eof(ch);
	}