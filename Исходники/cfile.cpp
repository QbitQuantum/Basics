char * CFile::GetS (char * buf, size_t n) 
{
	char * t = buf;
	size_t i;
	int c;

for (i = 0; i < n - 1; i++) {
	do {
		if (m_cf.rawPosition >= m_cf.size) {
			*buf = 0;
			return (buf == t) ? NULL : t;
			}
		c = GetC ();
		if (c == 0 || c == 10)       // Unix line ending
			break;
		if (c == 13) {      // Mac or DOS line ending
			int c1 = GetC ();
			Seek ( -1, SEEK_CUR);
			if (c1 == 10) // DOS line ending
				continue;
			else            // Mac line ending
				break;
			}
		} while (c == 13);
 	if (c == 0 || c == 10 || c == 13)  // because cr-lf is a bad thing on the mac
 		break;   // and anyway -- 0xod is CR on mac, not 0x0a
	*buf++ = c;
	if (c == '\n')
		break;
	}
*buf++ = 0;
return  t;
}