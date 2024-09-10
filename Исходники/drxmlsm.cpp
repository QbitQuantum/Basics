void
XMLrd::SampConvert(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++) {
		if (__isascii(str[i])) {
#if 0
			if (str[i] == '\\') {  // skip over hex char codes
				if (str[++i] == 'x')
					i += 3;
			}
			else 
#endif
			if (SampStart) {
				if (str[i] == ' ') {
					SampStart = false;
					SampStartPos = i;
					SampEnd = true;
				}
			}
			else if (SampEnd) {
				if (strchr(" ,.?/!;:)}]=", str[i])) {
					if (i <= (SampStartPos + SampWordMin)) {
						SampEnd = false;
						SampStart = true;
					}
					else {
						assert(SampListLen);
						int len = SampListLen[SampListNum];
						bool uc = isupper(str[SampStartPos + 1]) ? true : false;
						memmove(&str[SampStartPos + 1 + len], &str[i], strlen(&str[i]) + 1);
						memcpy(&str[SampStartPos + 1], SampList[SampListNum], len);
						if (uc)
							str[SampStartPos + 1] = toupper(*SampList[SampListNum]);
						if (++SampListNum >= SampListCount)
							SampListNum = 0;
						SampEnd = false;
						SampDelay = 0;
					}
				}
			}
			else if (++SampDelay >= SampDelayLimit)
				SampStart = true;
		}
	}
	if (SampEnd) {
		SampEnd = false;
		SampStart = true;
	}
}