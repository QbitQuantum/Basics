BOOL IsUnicode(const char* pBuffer,int cb/*,LPBOOL lpbBOM,LPBOOL lpbReverse*/)
{
	int i = 0xFFFF;

	BOOL bIsTextUnicode;

	BOOL bHasBOM;
	BOOL bHasRBOM;

	if (!pBuffer || cb < 2)
		return FALSE;
	//DWORD IsTextUnicode(CONST PVOID pvBuffer, int cb,PINT pResult);
	//文本文件存在的问题是，它们的内容没有严格和明确的规则，因此很难确定该文件是包含ANSI字符还是Unicode字符。
	// IsTextUnicode使用一系列统计方法和定性方法，以便猜测缓存的内容。由于这不是一种确切的科学方法，因此IsTextUnicode有可能返回不正确的结果。
	//第一个参数pvBuffer用于标识要测试的缓存的地址。该数据是个无效指针，因为你不知道你拥有的是ANSI字符数组还是Unicode字符数组。
	//第二个参数cb用于设定pvBuffer指向的字节数。同样，由于你不知道缓存中放的是什么，因此cb是个字节数，而不是字符数。
	//	请注意，不必设定缓存的整个长度。当然，IsTextUnicode能够测试的字节越多，得到的结果越准确。
	//第三个参数pResult是个整数的地址，必须在调用IsTextUnicode之前对它进行初始化。
	//	对该整数进行初始化后，就可以指明你要IsTextUnicode执行哪些测试。也可以为该参数传递NULL，
	//	在这种情况下，IsTextUnicode将执行它能够进行的所有测试（详细说明请参见PlatformSDK文档）。
	//如果IsTextUnicode认为缓存包含Unicode文本，便返回TRUE，否则返回FALSE。
	//	确实是这样，尽管Microsoft将该函数的原型规定为返回DWORD，但是它实际上返回一个布尔值。
	//	如果在pResult参数指向的整数中必须进行特定的测试，该函数就会在返回之前设定整数中的信息位，以反映每个测试的结果。

	bIsTextUnicode = IsTextUnicode(pBuffer, cb, &i);

	bHasBOM  = (*((UNALIGNED PWCHAR)pBuffer) == 0xFEFF);
	bHasRBOM = (*((UNALIGNED PWCHAR)pBuffer) == 0xFFFE);

	if (i == 0xFFFF) // i doesn't seem to have been modified ...
		i = 0;

	if (bIsTextUnicode || bHasBOM || bHasRBOM ||
		((i & (IS_TEXT_UNICODE_UNICODE_MASK | IS_TEXT_UNICODE_REVERSE_MASK)) &&
		!((i & IS_TEXT_UNICODE_UNICODE_MASK) && (i & IS_TEXT_UNICODE_REVERSE_MASK)) &&
		!(i & IS_TEXT_UNICODE_ODD_LENGTH) &&
		!(i & IS_TEXT_UNICODE_ILLEGAL_CHARS && !(i & IS_TEXT_UNICODE_REVERSE_SIGNATURE)) &&
		!((i & IS_TEXT_UNICODE_REVERSE_MASK) == IS_TEXT_UNICODE_REVERSE_STATISTICS))) 
	{

			//if (lpbBOM)
			//	*lpbBOM = (bHasBOM || bHasRBOM ||
			//	(i & (IS_TEXT_UNICODE_SIGNATURE | IS_TEXT_UNICODE_REVERSE_SIGNATURE)))
			//	? TRUE : FALSE;

			//if (lpbReverse)
			//	*lpbReverse = (bHasRBOM || (i & IS_TEXT_UNICODE_REVERSE_MASK)) ? TRUE : FALSE;

			return TRUE;
	}
	else
		return FALSE;
}