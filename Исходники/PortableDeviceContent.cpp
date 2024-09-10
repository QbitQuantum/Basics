JNIEXPORT jstring JNICALL Java_jmtp_PortableDeviceContentImplWin32_createObjectWithPropertiesAndData
	(JNIEnv* env, jobject obj, jobject jobjValues, jobject jobjFile)
{
	//variabelen
	HRESULT hr;
	IPortableDeviceContent* pDeviceContent;
	IPortableDeviceValues* pDeviceObjectValues;
	jobject jobjValuesReference;
	jstring jsFileLocation;
	LPWSTR wszFileLocation;
	DWORD dwBufferSize;
	CComPtr<IStream> pFileStream;
	CComPtr<IStream> pDeviceStream;
	CComPtr<IPortableDeviceDataStream> pDeviceDataStream;
	STATSTG fileStats;
	BYTE* pBuffer;
	DWORD dwReadFromStream;
	LPWSTR wszObjectID;
	jstring jsObjectID;
	jmethodID mid;


	//Methode implementatie
	pDeviceContent = GetPortableDeviceContent(env, obj);
	jobjValuesReference = RetrieveCOMReferenceFromCOMReferenceable(env, jobjValues);
	pDeviceObjectValues = (IPortableDeviceValues*)ConvertComReferenceToPointer(env, jobjValuesReference);
	
	//COM stream object aanmaken
	mid = env->GetMethodID(env->FindClass("java/io/File"), "getAbsolutePath", "()Ljava/lang/String;");
	jsFileLocation = (jstring)env->CallObjectMethod(jobjFile, mid);
	wszFileLocation = (WCHAR*)env->GetStringChars(jsFileLocation, NULL);
	hr = SHCreateStreamOnFileW(wszFileLocation, STGM_READ, &pFileStream);
	env->ReleaseStringChars(jsFileLocation, (jchar*)wszFileLocation); //string resources terug vrijgeven

	if(SUCCEEDED(hr))
	{
		//groote van het bestand bepalen
		//(door een beperking in java op het gebied van unsigned integers, moeten we het wel in c++ doen)
		pFileStream->Stat(&fileStats, STATFLAG_NONAME);
		pDeviceObjectValues->SetUnsignedLargeIntegerValue(WPD_OBJECT_SIZE, fileStats.cbSize.QuadPart);

		hr = pDeviceContent->CreateObjectWithPropertiesAndData(pDeviceObjectValues, 
			&pDeviceStream, &dwBufferSize, NULL);
		
		if(SUCCEEDED(hr))
		{
			pDeviceStream->QueryInterface(IID_IPortableDeviceDataStream, (void**)&pDeviceDataStream);

			//data kopieren
			pBuffer = new BYTE[dwBufferSize];
			dwReadFromStream = 0;
			do
			{
				pFileStream->Read(pBuffer, dwBufferSize, &dwReadFromStream);
				pDeviceDataStream->Write(pBuffer, dwReadFromStream, NULL);
			}
			while(dwReadFromStream > 0);
			delete[] pBuffer;
			hr = pDeviceDataStream->Commit(STGC_DEFAULT);

			if(SUCCEEDED(hr))
			{
				pDeviceDataStream->GetObjectID(&wszObjectID);
				jsObjectID = (jstring)env->NewString((jchar*)wszObjectID, wcslen(wszObjectID));
				CoTaskMemFree(wszObjectID);
				return jsObjectID;
			}
			else
			{
				ThrowCOMException(env, L"Couldn't commit the data to the portable device", hr);
			}
		}
		else
		{
			ThrowCOMException(env, L"Couldn't create a COM stream object to the portable device", hr);
		}
	}
	else
	{
		ThrowCOMException(env, L"Couldn't create a COM stream object to the file", hr);
	}

	return NULL;
}