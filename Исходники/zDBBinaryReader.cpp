array<__wchar_t>^ zDBBinaryReader::ToChars(int offset, int length)
{
	int							cb;				// Local size information
	const wchar_t*				pwchData;		// Pointer into raw data
	array<__wchar_t>^			rg;				// Managed char array of data
	PinnedCharPtr				pinRg;			// Pinned pointer into rg[]
	int							cch;			// Unicode character count

	CHECK_DISPOSED(m_disposed);
	if(offset < 0) throw gcnew ArgumentException();
	if(length < 0) throw gcnew ArgumentException();
	if((offset % sizeof(wchar_t)) != 0) throw gcnew ArgumentException();
	if((length % sizeof(wchar_t)) != 0) throw gcnew ArgumentException();

	// When accessing things as Unicode character data, ask SQLite for a
	// specific size that will properly adjusted as necessary

	cb = sqlite3_column_bytes16(m_pStatement->Handle, m_ordinal);
	if((offset + length) > cb) throw gcnew ArgumentOutOfRangeException();

	// Special case: If the caller wants zero bytes, don't go pinning
	// pointers and copying nothing.  Just return what they want

	if(length == 0) return gcnew array<__wchar_t>(0);

	cch = length / sizeof(wchar_t);				// Calculate character count
	rg = gcnew array<__wchar_t>(cch);			// Create return array
	pinRg = &rg[0];								// Pin and get a pointer

	// Only copy the amount of data that the caller is looking for from
	// the SQLite buffer into the managed Char array buffer

	pwchData = reinterpret_cast<const wchar_t*>(sqlite3_column_text16(m_pStatement->Handle, m_ordinal));
	wmemcpy_s(pinRg, cch, pwchData + (offset / sizeof(wchar_t)), cch);
	return rg;
}