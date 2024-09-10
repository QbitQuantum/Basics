wxThread::ExitCode FileDownloadTask::TaskStart()
{
	if (m_message.IsEmpty())
		SetStatus(wxString::Format(_("Downloading file from %s..."), m_src.c_str()));
	else
		SetStatus(m_message);
	
	double downloadSize = GetDownloadSize();
	
	if (downloadSize < 0)
	{
		successful = false;
		wxString baseError = _("An error occurred when downloading the file.\n");
		switch (-(int)downloadSize)
		{
		case 404:
			EmitErrorMessage(baseError + _("Error 404, the page could not be found."));
			return (ExitCode)0;
			
		default:
			EmitErrorMessage(baseError + wxString::Format(_("Unknown error %i occurred."), -(int)downloadSize));
			return (ExitCode)0;
		}
	}
	
	CURL *curl = curl_easy_init();
	
	curl_easy_setopt(curl, CURLOPT_URL, TOASCII(m_src));
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlLambdaCallback);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
	curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 20);
	
	size_t downloadedSize = 0;
	wxFFileOutputStream outStream(m_dest.GetFullPath());
	CurlLambdaCallbackFunction curlWrite = [&] (void *buffer, size_t size) -> size_t
	{
		outStream.Write(buffer, size);
		size_t lastwrite = outStream.LastWrite();
		downloadedSize += lastwrite;
		int progress = ((double)downloadedSize / (double)downloadSize) * 100;
		SetProgress(progress);

		wxString sDownloadedSize = _("???");

		if(progress >= 100 || downloadedSize > downloadSize)
		{
			sDownloadedSize = wxString::Format(wxT("%.0f"), (float)(downloadSize / 1000));
		}
		else
		{
			sDownloadedSize = wxString::Format(wxT("%.0f"), (float)(downloadedSize / 1000));
		}

		wxString sDownloadSize = wxString::Format(wxT("%.0f"), (float)(downloadSize / 1000));
		SetStatus(wxString::Format(_("Downloading...\n(%skB/%skB)"), sDownloadedSize.c_str(), sDownloadSize.c_str()));
		return outStream.LastWrite();
	};
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlWrite);
	
	int curlErr = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	
	if (curlErr != 0)
	{
		EmitErrorMessage(_("Download failed."));
		successful = false;
		return (ExitCode)0;
	}
	else
	{
		successful = true;
		return (ExitCode)1;
	}
}