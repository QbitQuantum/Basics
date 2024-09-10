//デバッグ用 認識結果をWaveファイルとして保存する
xreturn::r<bool> Recognition_SAPI::DebugSaveWavFile(const std::string& directory,ISpStreamFormat* streamFormat) const
{
	HRESULT hr;
	_USE_WINDOWS_ENCODING;

	const SPSTREAMFORMAT spFormat = SPSF_22kHz8BitMono;
	CSpStreamFormat Fmt( spFormat, &hr);
	if(FAILED(hr))	 return xreturn::windowsError(hr);

	{
		CSpStreamFormat OriginalFmt;
		{
			OriginalFmt.AssignFormat(streamFormat);

			// basic SAPI-stream for file-based storage
			CComPtr<ISpStream> cpStream;
			{
				ULONG cbWritten = 0;

				// create file on hard-disk for storing recognized audio, and specify audio format as the retained audio format
				std::string fff = directory + "\\" + num2str(time(NULL))+".wav";
				hr = SPBindToFile(_A2W(fff.c_str()) , SPFM_CREATE_ALWAYS, &cpStream, &OriginalFmt.FormatId(), OriginalFmt.WaveFormatExPtr(), SPFEI_ALL_EVENTS);
				if(FAILED(hr))	 return xreturn::windowsError(hr);

				// Continuously transfer data between the two streams until no more data is found (i.e. end of stream)
				// Note only transfer 1000 bytes at a time to creating large chunks of data at one time
				while (TRUE)
				{
					// for logging purposes, the app can retrieve the recognized audio stream length in bytes
					STATSTG stats;
					hr = streamFormat->Stat(&stats, NULL);
					if(FAILED(hr))	 return xreturn::windowsError(hr);

					// create a 1000-byte buffer for transferring
					BYTE bBuffer[1000];
					ULONG cbRead;

					// request 1000 bytes of data from the input stream
					hr = streamFormat->Read(bBuffer, 1000, &cbRead);
					// if data was returned??
					if (SUCCEEDED(hr) && cbRead > 0)
					{
						// then transfer/write the audio to the file-based stream
						hr = cpStream->Write(bBuffer, cbRead, &cbWritten);
						if(FAILED(hr))	 return xreturn::windowsError(hr);
					}

					// since there is no more data being added to the input stream, if the read request returned less than expected, the end of stream was reached, so break data transfer loop
					if (cbRead < 1000)
					{
						break;
					}
				}
			}
			// explicitly close the file-based stream to flush file data and allow app to immediately use the file
			hr = cpStream->Close();
			if(FAILED(hr))	 return xreturn::windowsError(hr);
		}
	}
	return true;
}