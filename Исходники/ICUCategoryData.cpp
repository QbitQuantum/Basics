status_t
ICUCategoryData::_GetConverter(UConverter*& converterOut)
{
	// we use different converters per thread to avoid concurrent accesses
	ICUThreadLocalStorageValue* tlsValue = NULL;
	status_t result = ICUThreadLocalStorageValue::GetInstanceForKey(
		fThreadLocalStorageKey, tlsValue);
	if (result != B_OK)
		return result;

	if (tlsValue->converter != NULL) {
		if (strcmp(tlsValue->charset, fGivenCharset) == 0) {
			converterOut = tlsValue->converter;
			return B_OK;
		}

		// charset no longer matches the converter, we need to dump it and
		// create a new one
		ucnv_close(tlsValue->converter);
		tlsValue->converter = NULL;
	}

	// create a new converter for the current charset
	UErrorCode icuStatus = U_ZERO_ERROR;
	UConverter* icuConverter = ucnv_open(fGivenCharset, &icuStatus);
	if (icuConverter == NULL)
		return B_NAME_NOT_FOUND;

	// setup the new converter to stop upon any errors
	icuStatus = U_ZERO_ERROR;
	ucnv_setToUCallBack(icuConverter, UCNV_TO_U_CALLBACK_STOP, NULL, NULL, NULL,
		&icuStatus);
	if (!U_SUCCESS(icuStatus)) {
		ucnv_close(icuConverter);
		return B_ERROR;
	}
	icuStatus = U_ZERO_ERROR;
	ucnv_setFromUCallBack(icuConverter, UCNV_FROM_U_CALLBACK_STOP, NULL, NULL,
		NULL, &icuStatus);
	if (!U_SUCCESS(icuStatus)) {
		ucnv_close(icuConverter);
		return B_ERROR;
	}

	tlsValue->converter = icuConverter;
	strlcpy(tlsValue->charset, fGivenCharset, sizeof(tlsValue->charset));

	converterOut = icuConverter;

	return B_OK;
}