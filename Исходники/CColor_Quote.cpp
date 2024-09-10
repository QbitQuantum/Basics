int CColor_Quote::Match_QuoteStr( const wchar_t* pszQuote, int nQuoteLen, int nPos, const CStringRef& cLineStr, bool bEscape )
{
	int nCharChars;
	int i;
	const int nCompLen = cLineStr.GetLength() - nQuoteLen + 1;
	const WCHAR quote1 = pszQuote[0];
	const WCHAR* pLine = cLineStr.GetPtr();
	for( i = nPos; i < nCompLen; i += nCharChars ){
		if( quote1 == pLine[i] && wmemcmp( pszQuote + 1, pLine + i + 1, nQuoteLen - 1 ) == 0 ){
			return i + nQuoteLen;
		}
		nCharChars = (Int)t_max(CLogicInt(1), CNativeW::GetSizeOfChar( pLine, cLineStr.GetLength(), i ));
		if( bEscape && pLine[i] == L'\\' ){
			i += (Int)t_max(CLogicInt(1), CNativeW::GetSizeOfChar( pLine, cLineStr.GetLength(), i + nCharChars ));
		}
	}
	return cLineStr.GetLength();
}