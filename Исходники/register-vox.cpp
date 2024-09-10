int wmain(int argc, WCHAR *argv[])
{
	USES_CONVERSION;
	HRESULT hr;

	::CoInitialize(NULL);

	ISpObjectToken *cpToken;
	ISpDataKey *cpDataKeyAttribs;

	hr = SpCreateNewTokenEx(
		SPCAT_VOICES, 

		/* CHANGEME: Change the following five arguments for your voice. */
		L"CMUKal",                    /* A unique name for your voice. */
		&CLSID_FliteCMUKalDiphoneObj, /* The CLSID for your voice object. */
		L"CMU Kal Diphone Voice",     /* Language-independent full name. */
		0x409,                        /* Language ID (US English is 0x409) */
		L"CMU Kal Diphone Voice",     /* Language-dependent full name. */

		&cpToken,
		&cpDataKeyAttribs);

	//--- Set additional attributes for searching and the path to the
	//    voice data file we just created.
	if (SUCCEEDED(hr))
	{
		/* CHANGEME: The gender of your speaker. */
                hr = cpDataKeyAttribs->SetStringValue(L"Gender",
						      L"Male");

		/* CHANGEME: The name of your speaker. */
                if (SUCCEEDED(hr))
			hr = cpDataKeyAttribs->SetStringValue(L"Name",
							      L"CMU Kal Diphone");

		/* CHANGEME: The language IDs supported by your voice. */
                if (SUCCEEDED(hr))
			hr = cpDataKeyAttribs->SetStringValue(L"Language",
							      /* US English;
								 English */
							      L"409;9");

		/* CHANGEME: The general age of your speaker (Adult, Child). */
                if (SUCCEEDED(hr))
			hr = cpDataKeyAttribs->SetStringValue(L"Age",
							      L"Adult");

		/* CHANGEME: The vendor name for your voice. */
                if (SUCCEEDED(hr))
			hr = cpDataKeyAttribs->SetStringValue(L"Vendor",
							      L"CMU");
	}
	::CoUninitialize();

	if (FAILED(hr)) {
		fprintf(stderr, "SpCreateNewTokenEx failed, code %x\n",
			FAILED(hr));
		return FAILED(hr);
	}

	return 0;
}