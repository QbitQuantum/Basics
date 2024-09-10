void charsetFilteredOutputStream_icu::flush()
{
	if (m_from == NULL || m_to == NULL)
		throw exceptions::charset_conv_error("Cannot initialize converters.");

	// Allocate buffer for Unicode chars
	const size_t uniSize = ucnv_getMinCharSize(m_from) * 1024 * sizeof(UChar);
	std::vector <UChar> uniBuffer(uniSize);

	// Conversion loop (with flushing)
	UErrorCode toErr = U_ZERO_ERROR;

	const char* uniSource = 0;
	const char* uniSourceLimit = 0;

	do
	{
		// Convert from source charset to Unicode
		UChar* uniTarget = &uniBuffer[0];
		UChar* uniTargetLimit = &uniBuffer[0] + uniSize;

		toErr = U_ZERO_ERROR;

		ucnv_toUnicode(m_from, &uniTarget, uniTargetLimit,
		               &uniSource, uniSourceLimit, NULL, /* flush */ TRUE, &toErr);

		if (U_FAILURE(toErr) && toErr != U_BUFFER_OVERFLOW_ERROR)
		{
			throw exceptions::charset_conv_error
				("[ICU] Error converting to Unicode from '" + m_sourceCharset.getName() + "'.");
		}

		const size_t uniLength = uniTarget - &uniBuffer[0];

		// Allocate buffer for destination charset
		const size_t cpSize = ucnv_getMinCharSize(m_to) * uniLength;
		std::vector <char> cpBuffer(cpSize);

		// Convert from Unicode to destination charset
		UErrorCode fromErr = U_ZERO_ERROR;

		const UChar* cpSource = &uniBuffer[0];
		const UChar* cpSourceLimit = &uniBuffer[0] + uniLength;

		do
		{
			char* cpTarget = &cpBuffer[0];
			char* cpTargetLimit = &cpBuffer[0] + cpSize;

			fromErr = U_ZERO_ERROR;

			ucnv_fromUnicode(m_to, &cpTarget, cpTargetLimit,
							 &cpSource, cpSourceLimit, NULL, /* flush */ TRUE, &fromErr);

			if (fromErr != U_BUFFER_OVERFLOW_ERROR && U_FAILURE(fromErr))
			{
				throw exceptions::charset_conv_error
					("[ICU] Error converting from Unicode to '" + m_destCharset.getName() + "'.");
			}

			const size_t cpLength = cpTarget - &cpBuffer[0];

			// Write successfully converted bytes
			m_stream.write(&cpBuffer[0], cpLength);

		} while (fromErr == U_BUFFER_OVERFLOW_ERROR);

	} while (toErr == U_BUFFER_OVERFLOW_ERROR);

	m_stream.flush();
}