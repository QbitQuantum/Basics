	HRESULT XMLFile::LoadFromFile(CString fn)
	{
		root->Clear();

		CComPtr<IXmlReader>		reader;
		CComPtr<IStream>		stream;
		HRESULT					hr = NOERROR;

		do {
			// create file stream
			hr = SHCreateStreamOnFile(fn, STGM_READ | STGM_SHARE_DENY_WRITE, &stream);
			if (FAILED(hr)) 
				break;

			// reader
			hr = CreateXmlReader(IID_IXmlReader, (void**)&reader, NULL);
			if (FAILED(hr)) 
				break;

			// select input
			hr = reader->SetInput(stream);
			if (FAILED(hr)) 
				break;

			int ret = LoadFromXmlReader(reader);
			if (ret < 0) {
				hr = ret;
			} else {
				hr = NOERROR;
			}
		} while (0);

		return hr;
	}	