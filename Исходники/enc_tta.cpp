	unsigned int __declspec(dllexport) GetAudioTypes3(int idx, char *desc)
	{
		if (idx == 0)
		{
			GetLocalisationApiService();
			StringCchPrintfA(desc, 1024, WASABI_API_LNGSTRING(IDS_ENC_TTA_DESC), VERSION, LIBTTA_VERSION);
			return mmioFOURCC('T', 'T', 'A', ' ');
		}
		return 0;
	}