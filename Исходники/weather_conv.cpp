// convert \t to tab and \n to linefeed
void ConvertBackslashes(char *str) 
{
	for (char *pstr=str; *pstr; pstr = CharNextA(pstr)) {
		if (*pstr == '\\') {
			switch(pstr[1]) {
				case 'n': *pstr = '\n'; break;
				case 't': *pstr = '\t'; break;
				default: *pstr = pstr[1]; break;
			}
			memmove(pstr+1, pstr+2, strlen(pstr+2)+1);
}	}	}