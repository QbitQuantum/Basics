char *ICUStringMgr::upperUTF8(char *buf, unsigned int maxlen) const {
	char *ret = buf;
	int max = (maxlen) ? maxlen : strlen(buf);
		
	UErrorCode err = U_ZERO_ERROR;
		
	if (!buf || !max) {
		return ret;
	}
		
	UChar *lowerStr = new UChar[max+10];
	UChar *upperStr = new UChar[max+10];
		
	u_strFromUTF8(lowerStr, max+9, 0, buf, -1, &err);
	if (err != U_ZERO_ERROR) {
//		SWLog::getSystemLog()->logError("from: %s", u_errorName(err));
		delete [] lowerStr;
		delete [] upperStr;
		return ret;
	}

	u_strToUpper(upperStr, max+9, lowerStr, -1, 0, &err);
	if (err != U_ZERO_ERROR) {
//		SWLog::getSystemLog()->logError("upperCase: %s", u_errorName(err));
		delete [] lowerStr;
		delete [] upperStr;
		return ret;
	}

	ret = u_strToUTF8(ret, max, 0, upperStr, -1, &err);
		
	delete [] lowerStr;
	delete [] upperStr;
	return ret;
}