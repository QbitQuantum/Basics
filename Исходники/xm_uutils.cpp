void CountWords(const UnicodeString& ustr, size_t& cnt, size_t& ctrl_cnt, size_t& sp_cnt)
{
	UErrorCode status = U_ZERO_ERROR;
	boost::scoped_ptr<BreakIterator> bi (
			BreakIterator::createWordInstance(Locale::getDefault(), status)
			);
	bi->setText(ustr);
	int32_t i = bi->first();
	while (i < ustr.length())
	{
		++cnt;

		UChar32 ch = ustr.char32At(i);

		if (u_iscntrl(ch))
			++ctrl_cnt;
		else if(u_isspace(ch))
			++sp_cnt;

		i = bi->next();
	}
}