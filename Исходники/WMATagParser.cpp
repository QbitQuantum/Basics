	jobject ExtractProperties(JNIEnv* env)
	{
		HRESULT hr = m_pReader->QueryInterface(IID_IWMHeaderInfo3, (void**)&m_pHeaderInfo);
		if (FAILED(hr))
			return NULL;

		static jclass mapClass = (jclass) env->NewGlobalRef(env->FindClass("java/util/HashMap"));
		static jmethodID mapConstruct = env->GetMethodID(mapClass, "<init>", "()V");
		static jmethodID mapPut = env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
		jobject rvMap = env->NewObject(mapClass, mapConstruct);
		
		WORD    cAttributes = 0;
		WCHAR*  pwszName    = NULL;
		WORD    cchName     = 0;
		BYTE*   pbValue     = NULL;
		DWORD   cbValue     = 0;
		WORD    langIndex   = 0;
		WORD    attIndex    = 0;

		WMT_ATTR_DATATYPE attType;

		// Get the total number of attributes in the file.

		hr = m_pHeaderInfo->GetAttributeCountEx(0xFFFF, &cAttributes);
		if (FAILED(hr))
			return NULL;

		// Loop through all the attributes, retrieving and displaying each.
		for(attIndex = 0; attIndex < cAttributes; attIndex++)
		{
			// Get the required buffer lengths for the name and value.

			hr = m_pHeaderInfo->GetAttributeByIndexEx(0xFFFF,
													attIndex,
													NULL,
													&cchName,
													NULL,
													NULL,
													NULL,
													&cbValue);
			if (FAILED(hr))
				continue;

			// Allocate the buffers.

			pwszName = new WCHAR[cchName];
			pbValue = new BYTE[cbValue];

			// Get the attribute.

			hr = m_pHeaderInfo->GetAttributeByIndexEx(0xFFFF,
													attIndex,
													pwszName,
													&cchName,
													&attType,
													&langIndex,
													pbValue,
													&cbValue);
			if (FAILED(hr))
			{
				delete [] pwszName;
				delete [] pbValue;
				continue;
			}

			// Display the attribute global index and name.

			// Display the attribute depending upon type.
			WCHAR* attValueName = new WCHAR[cbValue + 64];
			switch(attType)
			{
			case WMT_TYPE_QWORD:
				_ui64tow( *((QWORD*)pbValue), attValueName, 10);
				break;
			case WMT_TYPE_DWORD:
			case WMT_TYPE_WORD:
				swprintf(attValueName, L"%u", (DWORD) *pbValue);
				break;
			case WMT_TYPE_STRING:
				swprintf(attValueName, L"%s", (WCHAR*) pbValue);
				break;
			case WMT_TYPE_BOOL:
				swprintf(attValueName, L"%s", ((BOOL) *pbValue == TRUE) ? L"True" : L"False");
				break;
//			case WMT_TYPE_BINARY:
//			case WMT_TYPE_GUID:
			default:
				attValueName[0] = '\0';
				break;
			}

			if (attValueName[0] != '\0')
			{
				env->CallObjectMethod(rvMap, mapPut, env->NewString(reinterpret_cast<const jchar*>(pwszName), (int) wcslen(pwszName)), env->NewString(reinterpret_cast<const jchar*>(attValueName), (int) wcslen(attValueName)));
			}

			// Release allocated memory for the next pass.

			delete [] pwszName;
			delete [] pbValue;
			delete [] attValueName;
			cchName = 0;
			cbValue = 0;
		} // End for attIndex.

		return rvMap;
	}