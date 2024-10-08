utility::string_t Base64::constructBase64HeaderValue(const wchar_t* appendToBegin = 0, const wchar_t* dataToConvert = 0)
{

	if (dataToConvert == NULL)
		throw std::invalid_argument{ "Empty \"dataToConvert\" value of \"constructBase64HeaderValue\"" };

	size_t mByteCounter;
	char *pMBBuffer = (char*)malloc(BUFFER_SIZE);
	if (pMBBuffer == NULL)
		throw std::bad_alloc();
	// Convertin a sequence of wide characters to a corresponding sequence of multibyte characters for Unicode support
	_wcstombs_s_l(&mByteCounter, pMBBuffer, (size_t)BUFFER_SIZE, dataToConvert, (size_t)BUFFER_SIZE, _create_locale(LC_ALL, ".1251"));


	// Converting sequence of multibyte characters to vector of unsigned chars for using in conversions::to_base64
	std::string pString{ pMBBuffer };
	std::vector<unsigned char> vCred(mByteCounter - 1);
	std::transform(pString.begin(), pString.end(), vCred.begin(),
		[](wchar_t c)
	{
		return static_cast<wchar_t>(c);
	});

	// Data prepared, converting it to base64
	const auto b64cred{ conversions::to_base64(vCred) };

	if (appendToBegin == 0)
		return b64cred;
	else {
		// If something needs to be added before: composign header "Authorization" value
		utility::string_t valBegin{ appendToBegin };
		return valBegin.append(b64cred);
	}

	return 0;
}