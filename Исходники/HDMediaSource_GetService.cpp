HRESULT HDMediaSource::GetService(REFGUID guidService,REFIID riid,LPVOID *ppvObject)
{
	if (ppvObject == nullptr)
		return E_POINTER;

	if (guidService == MF_RATE_CONTROL_SERVICE) { //针对Store应用必须提供IMFRateControl接口
		return QueryInterface(riid,ppvObject);
	}else if (guidService == MF_METADATA_PROVIDER_SERVICE) {
#if !(WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP))
		return QueryInterface(riid,ppvObject);
#else
		CHAR szBuffer[MAX_PATH] = {};
		GetModuleFileNameA(nullptr,szBuffer,ARRAYSIZE(szBuffer));
		PathStripPathA(szBuffer);
		if (GetModuleHandleA("wmp.dll"))
		{
			if (_pMetadata)
			{
				ComPtr<IMFMetadata> pMetadata;
				if (SUCCEEDED(GetMFMetadata(_pPresentationDescriptor.Get(),0,0,pMetadata.GetAddressOf())))
					return QueryInterface(riid,ppvObject);
			}
		}else{
			return QueryInterface(riid,ppvObject);
		}
#endif
	}else if (guidService == MFNETSOURCE_STATISTICS_SERVICE) {
		if (_network_mode)
			return QueryInterface(riid,ppvObject);
	}else if (guidService == MF_SCRUBBING_SERVICE) {
		if (FAILED(MakeKeyFramesIndex()))
			return MF_E_UNSUPPORTED_SERVICE;
		return QueryInterface(riid,ppvObject);
	}

	return MF_E_UNSUPPORTED_SERVICE;
}