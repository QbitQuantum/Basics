// Преобразование символа в кодировке OEM в символ Windows.
const WCHAR CConvOem::fromOemW(const CHAR chSrc)
{
	if (m_blInvalidBuff)
	{
		SetLastError(ERROR_INVALID_ADDRESS);
		return WEOF;
	}
	OemToCharBuffW(&chSrc, m_szBuffW, 1);
	return *m_szBuffW;
}