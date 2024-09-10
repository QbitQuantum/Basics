size_t wxBZipOutputStream::OnSysWrite(const void* buffer, size_t bufsize)
{
	size_t nWrote = 0;
	int n;

	
	((bz_stream*&)hZip)->next_in = &(((char*&)buffer)[nWrote]);
	((bz_stream*&)hZip)->avail_in = bufsize - nWrote;
	((bz_stream*&)hZip)->next_out = &pBuffer[0];
	((bz_stream*&)hZip)->avail_out = WXBZBS;

	do {
	if ((n=BZ2_bzCompress((bz_stream*&)hZip, BZ_RUN)) != BZ_RUN_OK)
	{

		wxMessageBox(wxString::Format("BrokeC %i", n));
		break;
	}
	if (((bz_stream*&)hZip)->avail_out < WXBZBS)
	{
		((bz_stream*&)hZip)->next_out = &pBuffer[0];
		((bz_stream*&)hZip)->avail_out = WXBZBS;
		size_t nCurWrite = WXBZBS - ((bz_stream*&)hZip)->avail_out;
	//	wxMessageBox(wxString::Format("%i", nCurWrite));
		WriteRaw(pBuffer, nCurWrite);
		nWrote += m_parent_o_stream->LastWrite();


		if (m_parent_o_stream->LastWrite() != nCurWrite)
		{
			wxMessageBox("Broke");
			break;
		}
	}
	} while(((bz_stream*&)hZip)->avail_in != 0);

	while (nWrote != bufsize)
	{
		((bz_stream*&)hZip)->next_out = &pBuffer[0];
		((bz_stream*&)hZip)->avail_out = WXBZBS;

		int nRet = BZ2_bzCompress((bz_stream*&)hZip, BZ_FINISH);
		
		if (nRet != BZ_FINISH_OK && nRet != BZ_STREAM_END)
		{
			wxMessageBox("ErrorFK");
			break;
		}

		
		size_t nCurWrite = WXBZBS - ((bz_stream*&)hZip)->avail_out;
	//	wxMessageBox(wxString::Format("%i", nCurWrite));
		if (nCurWrite != 0)
		{
			WriteRaw(pBuffer, nCurWrite);
			nWrote += m_parent_o_stream->LastWrite();


			if (m_parent_o_stream->LastWrite() != nCurWrite)
			{
				wxMessageBox("Broke");
				break;
			}
		}

		if (nRet == BZ_STREAM_END)
		{
			wxMessageBox("GOOD");
			break;
		}

	}
 
//	wxMessageBox(wxString::Format("%i %i", nWrote, bufsize);
	return nWrote;	
}