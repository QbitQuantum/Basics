TextToken* TextToken::tokenizeBBCodes(const wchar_t *text, int l) {
	static wchar_t *bbTagName[] = {L"b", L"i", L"u", L"img", L"color", L"size"};
	static int 		bbTagNameLen[] = {1, 1, 1, 3, 5, 4};
	static int 		bbTagArg[] = {0, 0, 0, 0, 1, 1};
	static int 		bbTagId[] = {BB_B, BB_I, BB_U, BB_IMG, BB_COLOR, BB_SIZE};
	static int      bbTagEnd[6];
	static int      bbTagCount[6];
	int i,j;
   	TextToken *firstToken = NULL, *lastToken = NULL, * bbToken = NULL;
    int textLen = 0;
	for (j = 0; j < 6; j++) {
		bbTagCount[j] = 0;
		bbTagEnd[j] = 0;
	}
    for (i = 0; i <= l;) {
		int k, tagArgStart=0, tagArgEnd=0, tagDataStart=0, newTokenType = 0, newTokenSize = 0;
		bool bbFound = false;
		if (text[i] == '[') {
			if (text[i+1] != '/') {
				for (j = 0; j < 6; j++) {
					k = i + 1;
					if (!wcsnicmp(text+k, bbTagName[j], bbTagNameLen[j])) {
						tagArgStart = tagArgEnd = 0;
						k += bbTagNameLen[j];
						if (bbTagArg[j]) {
							if (text[k] != '=') continue;
							k++;
							tagArgStart = k;
							for (; text[k]!='\0'; k++) {
								if ((text[k]>='0' && text[k]<='9') ||
									(text[k]>='A' && text[k]<='Z') ||
									(text[k]>='a' && text[k]<='z') ||
									(text[k]=='#')) continue;
								break;
							}
							tagArgEnd = k;
						}
						if (text[k] == ']') {
							k++;
							tagDataStart = k;
							if (k < bbTagEnd[j]) k = bbTagEnd[j];
							for (; k < l; k++) {
								if (text[k] == '[' && text[k+1] == '/') {
									k += 2;
									if (!wcsnicmp(text+k, bbTagName[j], bbTagNameLen[j])) {
										k += bbTagNameLen[j];
										if (text[k] == ']') {
											k++;
											bbFound = true;
											break;
										}
									}
								}
							}
							if (bbFound) break;
						}
					}
				}
				if (bbFound) {
                    bbTagEnd[j] = k;
					switch (bbTagId[j]) {
					case BB_B:
					case BB_I:
					case BB_U:
					case BB_COLOR:
					case BB_SIZE:
	                    bbTagCount[j]++;
						if (bbTagArg[j]) {
							bbToken = new TextToken(BBCODE, text + tagArgStart, tagArgEnd - tagArgStart);
						} else {
							bbToken = new TextToken(BBCODE, bbTagName[j], bbTagNameLen[j]);
						}
						bbToken->setEnd(false);
						bbToken->setTag(bbTagId[j]);
						newTokenType = BBCODE;
						newTokenSize = tagDataStart - i;
						break;
					case BB_IMG:
						bbToken = new TextToken(BBCODE, text + tagDataStart, k - 6 - tagDataStart);
						bbToken->setTag(bbTagId[j]);
						bbToken->setEnd(false);
						newTokenType = BBCODE;
						newTokenSize = k - i;
						break;
					}
				}
			} else {
				for (j = 0; j < 6; j++) {
					k = i + 2;
					if (bbTagCount[j]>0 && !wcsnicmp(text+k, bbTagName[j], bbTagNameLen[j])) {
						k += bbTagNameLen[j];
						if (text[k] == ']') {
							k++;
							bbFound = true;
							break;
						}
					}
				}
				if (bbFound) {
                    bbTagCount[j]--;
					bbToken = new TextToken(BBCODE, bbTagName[j], bbTagNameLen[j]);
					bbToken->setEnd(true);
					bbToken->setTag(bbTagId[j]);
					newTokenType = BBCODE;
					newTokenSize = k - i;
				}
			}
		}
		if (!bbFound) {
			if (i==l) {
				newTokenType = END;
				newTokenSize = 1;
			} else {
				newTokenType = TEXT;
				newTokenSize = 1;
			}
		}
		if (newTokenType != TEXT) {
			if (textLen >0 ) {
                TextToken *newToken = new TextToken(TEXT, text+i-textLen, textLen);
				textLen = 0;
				if (lastToken == NULL) {
					firstToken = newToken;
				} else {
				    lastToken->setNext(newToken);
				}
				lastToken = newToken;
			}
            if (newTokenType == BBCODE) {
				if (lastToken == NULL) {
					firstToken = bbToken;
				} else {
				    lastToken->setNext(bbToken);
				}
				lastToken = bbToken;
            }
		} else {
			textLen += newTokenSize;
		}
		i += newTokenSize;
    }
    return firstToken;
}