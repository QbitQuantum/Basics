//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
bool SystemMultiByteEncoding::ConvertFromUTF16(const byte_t* pInBuffer, size_t uInByteCount, byte_t* pOutBuffer, size_t uOutBufferByteCount, size_t* pBytesUsed, size_t* pCharsUsed, bool* pUsedDefaultChar) const
{
#ifdef LNOTE_WCHAR_16
	// wcsrtombs_s は変換したいサイズを指定することができず、基本的に \0 まで変換することになる。
	// そのため、一度別バッファに移して \0 を付ける
	ReferenceBuffer tmpWideBuffer;
	tmpWideBuffer.reserve(uInByteCount + sizeof(wchar_t));	// NULL 文字分
	tmpWideBuffer.copy(pInBuffer, uInByteCount);
	wchar_t* wideStr = (wchar_t*)tmpWideBuffer.getPointer();
	wideStr[uInByteCount / sizeof(wchar_t)] = L'\0';

	// Wide → Multi
	size_t convertedLen;
	mbstate_t mbstate = 0;
	::memset((void*)&mbstate, 0, sizeof(mbstate));
	errno_t err = wcsrtombs_s(
		&convertedLen,				// 変換された文字数が格納される (Multi への変換なので、バイト数)
		(char*)pOutBuffer,			// 出力先バッファ
		uOutBufferByteCount,		// 出力先バッファのサイズ (バイト数)
		(const wchar_t**)&wideStr,	// 変換元
		_TRUNCATE,					// 出力先バッファに格納できる最大バイト数 (実質↑↑と同じ。_TRUNCATE で \0 まで)
		&mbstate);
	LN_THROW(err == 0, ArgumentException);

	// 終端には \0 が強制的に付加される。純粋な文字部分のサイズが欲しいので -1 する。
	// TODO: つまり、出力バッファは ↑の第2引数 +1ワード分 確保しておく必要がある
	convertedLen--;

	// wcsrtombs_s じゃ文字数カウントはできないので UnicodeUtils を使う
	int count;
	if (LN::UnicodeUtils::GetUTF16CharCount((LN::UTF16*)pInBuffer, uInByteCount / sizeof(LN::UTF16), true, &count) != LN::UTFConversionResult_Success){
		return false;
	}

	*pBytesUsed = convertedLen;
	*pCharsUsed = count;
#else
	LN_THROW(0, NotImplementedException);
#endif
	return true;
}