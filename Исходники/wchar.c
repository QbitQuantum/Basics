/*
 * Verify mbstr to make sure that it has a valid character sequence.
 * mbstr is not necessarily NULL terminated; length of mbstr is
 * specified by len.
 *
 * If OK, return TRUE.	If a problem is found, return FALSE when noError is
 * true; when noError is false, ereport() a descriptive message.
 */
bool
pg_verifymbstr(const char *mbstr, int len, bool noError)
{
	int			l;
	int			i;
	int			encoding;

	/* we do not need any check in single-byte encodings */
	if (pg_database_encoding_max_length() <= 1)
		return true;

	encoding = GetDatabaseEncoding();

	while (len > 0 && *mbstr)
	{
		l = pg_mblen(mbstr);

		/* special UTF-8 check */
		if (encoding == PG_UTF8)
		{
			if (!pg_utf8_islegal((const unsigned char *) mbstr, l))
			{
				if (noError)
					return false;
				ereport(ERROR,
						(errcode(ERRCODE_CHARACTER_NOT_IN_REPERTOIRE),
						 errmsg("invalid UTF-8 byte sequence detected near byte 0x%02x",
								(unsigned char) *mbstr)));
			}
		}
		else
		{
			for (i = 1; i < l; i++)
			{
				/*
				 * we expect that every multibyte char consists of bytes
				 * having the 8th bit set
				 */
				if (i >= len || (mbstr[i] & 0x80) == 0)
				{
					char		buf[8 * 2 + 1];
					char	   *p = buf;
					int			j,
								jlimit;

					if (noError)
						return false;

					jlimit = Min(l, len);
					jlimit = Min(jlimit, 8);	/* prevent buffer overrun */

					for (j = 0; j < jlimit; j++)
						p += sprintf(p, "%02x", (unsigned char) mbstr[j]);

					ereport(ERROR,
							(errcode(ERRCODE_CHARACTER_NOT_IN_REPERTOIRE),
					errmsg("invalid byte sequence for encoding \"%s\": 0x%s",
						   GetDatabaseEncodingName(), buf)));
				}
			}
		}
		len -= l;
		mbstr += l;
	}
	return true;
}