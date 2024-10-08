char UTF8arShaping::processText(SWBuf &text, const SWKey *key, const SWModule *module)
{
        UChar *ustr, *ustr2;
	 if ((unsigned long)key < 2)	// hack, we're en(1)/de(0)ciphering
		return -1;

        int32_t len = text.length();
        ustr = new UChar[len];
        ustr2 = new UChar[len];

	// Convert UTF-8 string to UTF-16 (UChars)
        len = ucnv_toUChars(conv, ustr, len, text.c_str(), -1, &err);

        len = u_shapeArabic(ustr, len, ustr2, len, U_SHAPE_LETTERS_SHAPE | U_SHAPE_DIGITS_EN2AN, &err);

	   text.setSize(text.size()*2);
	   len = ucnv_fromUChars(conv, text.getRawData(), text.size(), ustr2, len, &err);
	   text.setSize(len);

        delete [] ustr2;
        delete [] ustr;
	return 0;
}