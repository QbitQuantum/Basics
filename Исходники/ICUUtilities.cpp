	void FStringConverter::ConvertString(const TCHAR* Source, const int32 SourceStartIndex, const int32 SourceLen, icu::UnicodeString& Destination, const bool ShouldNullTerminate)
	{
		if (SourceLen > 0)
		{
			UErrorCode ICUStatus = U_ZERO_ERROR;

			ucnv_reset(ICUConverter);

			// Get the internal buffer of the string, we're going to use it as scratch space
			const int32_t DestinationCapacityUChars = SourceLen * 2;
			UChar* InternalStringBuffer = Destination.getBuffer(DestinationCapacityUChars);

			// Perform the conversion into the string buffer
			const int32_t SourceSizeBytes = SourceLen * sizeof(TCHAR);
			const int32_t DestinationLength = ucnv_toUChars(ICUConverter, InternalStringBuffer, DestinationCapacityUChars, reinterpret_cast<const char*>(Source + SourceStartIndex), SourceSizeBytes, &ICUStatus);

			// Optionally null terminate the string
			if (ShouldNullTerminate)
			{
				InternalStringBuffer[DestinationLength] = 0;
			}

			// Size it back down to the correct size and release our lock on the string buffer
			Destination.releaseBuffer(DestinationLength);

			check(U_SUCCESS(ICUStatus));
		}
		else
		{
			Destination.remove();
		}
	}