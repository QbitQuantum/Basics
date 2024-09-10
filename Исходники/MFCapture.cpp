	bool VideoCapture::CreateSourceReaderAsync()
	{
		HRESULT hr;

		HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (hEvent == NULL)
		{
			MFUtil::ShowMessage(TEXT("CreateEvent Failed."), ML_ERROR);
			return false;
		}

		this->CallBack = new SourceReaderCallBack(hEvent);
		if (this->CallBack == NULL)
		{
			MFUtil::ShowMessage(TEXT("CreateCallBack Failed."), ML_ERROR);
			return false;
		}
	
		IMFAttributes *pAttributes = NULL;

		hr = MFCreateAttributes(&pAttributes, 1);
		if (hr != S_OK)
		{
			MFUtil::ShowMessage(TEXT("CreateAttributes Failed."), ML_ERROR);
			this->ReleaseDevices();
			return false;
		}

		hr = pAttributes->SetUnknown(MF_SOURCE_READER_ASYNC_CALLBACK, this->CallBack);
		if (hr != S_OK)
		{
			MFUtil::ShowMessage(TEXT("AttributeSetting Failed."), ML_ERROR);
			this->ReleaseDevices();
			return false;
		}

		pin_ptr<IMFSourceReader *> pSourceReader = &(this->SourceReader);
		hr = MFCreateSourceReaderFromMediaSource(this->Source, pAttributes, pSourceReader);
		if (hr != S_OK)
		{
			MFUtil::ShowMessage(TEXT("CreateSourceReader Failed."), ML_ERROR);
			this->ReleaseDevices();
			return false;
		}

		hr = this->ConfigureSourceReader();
		if (hr != S_OK)
		{
			MFUtil::ShowMessage(TEXT("ConfigureDecoder Failed."), ML_ERROR);
			MFUtil::ShowErrorNameFromCode(hr);
			return false;
		}

		// 二回目以降の ReadSample() はコールバック内で呼ぶため、
		// SourceReaderCallBack クラスにも SourceReader が必要。
		this->CallBack->SourceReader = this->SourceReader;

		return true;
	}