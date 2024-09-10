/*
 * Some notes about this function:
 * This function returns a list of available SAPI voices. It has been fixed and should be working correclty
 * on Windows 7 and all other versions of Windows.
 *
 * The solution to getting this function working was found here:
 * http://stackoverflow.com/questions/4336245/how-to-return-a-java-string-in-c-using-jni
 *
 * In addition to the above StackOverflow thread, it was necessary to change this function to return an std::string instance instead
 * of a character pointer, and to use stringstreams instead of CStrings.
 */
std::string SapiInterface::GetVoiceNative()
{
	
	std::stringstream sstream;
	sstream << "<?xml version=\"1.0\"?>";

	ISpVoice * pVoice = NULL;	
	CComPtr<ISpObjectToken>        cpVoiceToken;
	CComPtr<IEnumSpObjectTokens>   cpEnum;
	CComPtr<ISpVoice>              cpVoice;
	ULONG                          ulCount = 0;

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	if(SUCCEEDED(hr))
	{
		WCHAR   **m_ppszTokenIds;
		USES_CONVERSION;
		CComPtr<IEnumSpObjectTokens>    cpEnum;
		WCHAR**							szDescription;
		ISpObjectToken                  *pToken = NULL;
		CComPtr<ISpObjectToken>         cpVoiceToken; //the token is the voice
		CComPtr<ISpVoice>               cpVoice;
		ULONG                           ulCount = 0;

		if(SUCCEEDED(hr))
		{
			hr = cpVoice.CoCreateInstance( CLSID_SpVoice );
			if(SUCCEEDED(hr))
			{
				WCHAR *pszCurTokenId = NULL;
				ULONG ulIndex = 0, ulNumTokens = 0, ulCurToken = -1;

				hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &cpEnum);

				if (hr == S_OK)
				{
					hr = cpEnum->GetCount( &ulNumTokens );

					if (SUCCEEDED(hr) && ulNumTokens != 0)
					{
						szDescription = new WCHAR* [ulNumTokens];
						m_ppszTokenIds = new WCHAR* [ulNumTokens];

						ZeroMemory(m_ppszTokenIds, ulNumTokens * sizeof(WCHAR *));

						UINT i =0;
						while (cpEnum->Next(1, &pToken, NULL) == S_OK)
						{
							//Don't care about return value in next line:
							hr = SpGetDescription(pToken, &szDescription[ulIndex]);
							ulIndex++;

							int utf8_length = WideCharToMultiByte(
								  CP_UTF8,           // Convert to UTF-8
								  0,                 // No special character conversions required 
													 // (UTF-16 and UTF-8 support the same characters)
								  szDescription[i],             // UTF-16 string to convert
								  -1,                // utf16 is NULL terminated (if not, use length)
								  NULL,              // Determining correct output buffer size
								  0,                 // Determining correct output buffer size
								  NULL,              // Must be NULL for CP_UTF8
								  NULL);             // Must be NULL for CP_UTF8

							if (utf8_length == 0) {
								return std::string("WideCharToMultibyte error.");
							}
							
							char *utf8_voice = new char[utf8_length];
							utf8_length = WideCharToMultiByte(
							  CP_UTF8,           // Convert to UTF-8
							  0,                 // No special character conversions required 
												 // (UTF-16 and UTF-8 support the same characters)
							  szDescription[i],             // UTF-16 string to convert
							  -1,                // utf16 is NULL terminated (if not, use length)
							  utf8_voice,              // UTF-8 output buffer
							  utf8_length,       // UTF-8 output buffer size
							  NULL,              // Must be NULL for CP_UTF8
							  NULL);             // Must be NULL for CP_UTF8
							//strConcatenateXML += "<voice>" + szDescription[i] + "</voice>";

							sstream << "<voice>" << utf8_voice << "</voice>";
							pToken->Release();
							pToken = NULL;
							i++;
						}

						delete [] szDescription;
					}
					else
						{
						//strConcatenateXML = "No voice found. (5)";
						sstream << "No voice found. (5)";
					}
				}
				else
				{
					//strConcatenateXML = "No voice found. (4)";
					sstream << "No voice found. (4)";
				}
			}
			else
			{
				//strConcatenateXML = "No voice found. (3)";
				sstream << "No voice found. (3)";
			}
		}
		else
		{
			//strConcatenateXML = "No voice found. (2)";
			sstream << "No voice found. (2)";
		}
	}
	else
	{
		//strConcatenateXML = "No voice found. (1)";
		sstream << "No voice found. (1)";
	}

	return sstream.str();
}