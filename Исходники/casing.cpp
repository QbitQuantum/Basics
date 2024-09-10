/*
Function:
ChangeCaseTurkish

Performs upper or lower casing of a string into a new buffer, performing special
casing for Turkish.
*/
extern "C" void ChangeCaseTurkish(const UChar* lpSrc,
								  int32_t cwSrcLength,
								  UChar* lpDst,
								  int32_t cwDstLength,
								  int32_t bToUpper)
{
	// See algorithmic comment in ChangeCase.

	UBool isError = FALSE;
	int32_t srcIdx = 0, dstIdx = 0;
	UChar32 srcCodepoint, dstCodepoint;

	if (bToUpper)
	{
		while (srcIdx < cwSrcLength)
		{
			// In turkish casing, LATIN SMALL LETTER I (U+0069) upper cases to LATIN
			// CAPITAL LETTER I WITH DOT ABOVE (U+0130).
			U16_NEXT(lpSrc, srcIdx, cwSrcLength, srcCodepoint);
			dstCodepoint = ((srcCodepoint == (UChar32)0x0069) ? (UChar32)0x0130 : u_toupper(srcCodepoint));
			U16_APPEND(lpDst, dstIdx, cwDstLength, dstCodepoint, isError);
			assert(isError == FALSE && srcIdx == dstIdx);
		}
	}
	else
	{
		while (srcIdx < cwSrcLength)
		{
			// In turkish casing, LATIN CAPITAL LETTER I (U+0049) lower cases to
			// LATIN SMALL LETTER DOTLESS I (U+0131).
			U16_NEXT(lpSrc, srcIdx, cwSrcLength, srcCodepoint);
			dstCodepoint = ((srcCodepoint == (UChar32)0x0049) ? (UChar32)0x0131 : u_tolower(srcCodepoint));
			U16_APPEND(lpDst, dstIdx, cwDstLength, dstCodepoint, isError);
			assert(isError == FALSE && srcIdx == dstIdx);
		}
	}
}