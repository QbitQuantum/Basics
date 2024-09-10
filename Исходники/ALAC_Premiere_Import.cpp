AP4_Result
My_ByteStream::Seek(AP4_Position position)
{
#ifdef PRWIN_ENV
	LARGE_INTEGER lpos;

	lpos.QuadPart = position;

#if _MSC_VER < 1300
	DWORD pos = SetFilePointer(_fp, lpos.u.LowPart, &lpos.u.HighPart, FILE_BEGIN);

	BOOL result = (pos != 0xFFFFFFFF || NO_ERROR == GetLastError());
#else
	BOOL result = SetFilePointerEx(_fp, lpos, NULL, FILE_BEGIN);
#endif

	return (result ? AP4_SUCCESS : AP4_FAILURE);
#else
	OSErr result = FSSetForkPosition(CAST_REFNUM(_fp), fsFromStart, position);

	return (result == noErr ? AP4_SUCCESS : AP4_FAILURE);
#endif
}