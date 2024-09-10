static unsigned char*
_get_utf8_text(const id3_ucs4_t* native_text)
{
	unsigned char *utf8_text = NULL;
	char *in, *in8, *iconv_buf;
	iconv_result rc;
	int i, n;

	in = (char*)id3_ucs4_latin1duplicate(native_text);
	if(!in)
	{
		goto out;
	}

	in8 = (char*)id3_ucs4_utf8duplicate(native_text);
	if(!in8)
	{
		free(in);
		goto out;
	}

	iconv_buf = (char*)calloc(MAX_ICONV_BUF, sizeof(char));
	if(!iconv_buf)
	{
		free(in); free(in8);
		goto out;
	}

	i = lang_index;
	// (1) try utf8 -> default
	rc = do_iconv(iconv_map[i].cpnames[0], "UTF-8", in8, strlen(in8), iconv_buf, MAX_ICONV_BUF);
	if(rc == ICONV_OK)
	{
		utf8_text = (unsigned char*)in8;
		free(iconv_buf);
	}
	else if(rc == ICONV_TRYNEXT)
	{
		// (2) try default -> utf8
		rc = do_iconv("UTF-8", iconv_map[i].cpnames[0], in, strlen(in), iconv_buf, MAX_ICONV_BUF);
		if(rc == ICONV_OK)
		{
			utf8_text = (unsigned char*)iconv_buf;
		}
		else if(rc == ICONV_TRYNEXT)
		{
			// (3) try other encodes
			for(n = 1; n < N_LANG_ALT && iconv_map[i].cpnames[n]; n++)
			{
				rc = do_iconv("UTF-8", iconv_map[i].cpnames[n], in, strlen(in), iconv_buf, MAX_ICONV_BUF);
				if(rc == ICONV_OK)
				{
					utf8_text = (unsigned char*)iconv_buf;
					break;
				}
			}
			if(!utf8_text)
			{
				// cannot iconv
				utf8_text = (unsigned char*)id3_ucs4_utf8duplicate(native_text);
				free(iconv_buf);
			}
		}
		free(in8);
	}
	free(in);

 out:
	if(!utf8_text)
	{
		utf8_text = (unsigned char*)strdup("UNKNOWN");
	}

	return utf8_text;
}