char UTF8NFKD::processText(SWBuf &text, const SWKey *key, const SWModule *module)
{
	if ((unsigned long)key < 2)	// hack, we're en(1)/de(0)ciphering
		return -1;
        
	int32_t len =  5 + text.length() * 5;
        source = new UChar[len + 1]; //each char could become a surrogate pair

	// Convert UTF-8 string to UTF-16 (UChars)
        int32_t ulen = ucnv_toUChars(conv, source, len, text.c_str(), -1, &err);
        target = new UChar[len + 1];

        //compatability decomposition
        ulen = unorm_normalize(source, ulen, UNORM_NFKD, 0, target, len, &err);

	   text.setSize(len);
	   len = ucnv_fromUChars(conv, text.getRawData(), len, target, ulen, &err);
	   text.setSize(len);

	   delete [] source;
	   delete [] target;

	return 0;
}