bool COfficeFileFormatChecker::isOfficeFile(const std::wstring & _fileName)
{
#if defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
    std::wstring fileName = CorrectPathW(_fileName);
#else
    std::wstring fileName = _fileName;
#endif

    //приоритет как оказывается важен
    //Metamorphic Manual for windows 28415.doc
	POLE::Storage storage(fileName.c_str());
    if (storage.open())
    {
        if ( isDocFormatFile(&storage) )
        {
			//nFileType внутри
			return true;
        }
        else if ( isXlsFormatFile(&storage) )
        {
            nFileType = AVS_OFFICESTUDIO_FILE_SPREADSHEET_XLS;
            return true;
        }
        else if ( isPptFormatFile(&storage) )
        {
#if defined FILE_FORMAT_CHECKER_WITH_MACRO
			COfficePPTFile pptFile;
			
			bMacroEnabled = true;
			long nResult = pptFile.OpenFile(fileName, L"", bMacroEnabled);
			if (nResult != S_OK)
			{
				return false;
			}         
			pptFile.CloseFile();
#endif
			nFileType = AVS_OFFICESTUDIO_FILE_PRESENTATION_PPT;
            return true;
        }
        else if ( isMS_OFFCRYPTOFormatFile(&storage, sDocumentID) )
        {
            nFileType = AVS_OFFICESTUDIO_FILE_OTHER_MS_OFFCRYPTO;
            return true;
        }
	}

    COfficeUtils OfficeUtils(NULL);
    if (OfficeUtils.IsArchive(fileName) == S_OK)
	{
             if ( isOOXFormatFile(fileName) )           return true;
        else if ( isOpenOfficeFormatFile(fileName) )    return true;
        else if ( isOnlyOfficeFormatFile(fileName) )    return true;
        else if ( isXpsFile(fileName) )                 return true;
	}
//-----------------------------------------------------------------------------------------------
    // others
    {
        NSFile::CFileBinary file;
        if (!file.OpenFile(fileName))
            return false;
		
		unsigned char* buffer = new unsigned char[4096]; //enaf !!
        if (!buffer){file.CloseFile();return false;}

        DWORD dwReadBytes = 0;
        file.ReadFile(buffer, MIN_SIZE_BUFFER, dwReadBytes);
        int sizeRead = (int)dwReadBytes;

		if ( isRtfFormatFile(buffer,sizeRead) )
		{
			nFileType = AVS_OFFICESTUDIO_FILE_DOCUMENT_RTF;
		}
		else if ( isBinaryDoctFormatFile(buffer,sizeRead) )
		{
			nFileType = AVS_OFFICESTUDIO_FILE_CANVAS_WORD;
		}
		else if ( isBinaryXlstFormatFile(buffer,sizeRead) )
		{
			nFileType = AVS_OFFICESTUDIO_FILE_CANVAS_SPREADSHEET;
		}
		else if ( isBinaryPpttFormatFile(buffer,sizeRead) )
		{
			nFileType = AVS_OFFICESTUDIO_FILE_CANVAS_PRESENTATION;
		}        
        else if (isPdfFormatFile(buffer,sizeRead) )
        {
            nFileType = AVS_OFFICESTUDIO_FILE_CROSSPLATFORM_PDF;
        }
        else if (isDjvuFormatFile(buffer,sizeRead) )
        {
            nFileType = AVS_OFFICESTUDIO_FILE_CROSSPLATFORM_DJVU;
        }
		else if (isHtmlFormatFile(buffer,sizeRead, false))
        {
			long fileSize = file.GetFileSize();
			if (fileSize > MIN_SIZE_BUFFER)		
			{
				file.SeekFile(fileSize - MIN_SIZE_BUFFER);
				file.ReadFile(buffer, MIN_SIZE_BUFFER, dwReadBytes);
				int sizeRead = (int)dwReadBytes;
			}
			if (isHtmlFormatFile(buffer,sizeRead, true))
			{
				nFileType = AVS_OFFICESTUDIO_FILE_DOCUMENT_HTML;
			}
        }
        else if (isFB2FormatFile(buffer,sizeRead) )
        {
            nFileType = AVS_OFFICESTUDIO_FILE_DOCUMENT_FB2;
        }
		else if (isOpenOfficeFlatFormatFile(buffer,sizeRead) )
		{
			//nFileType
		}
		else if (isDocFlatFormatFile(buffer,sizeRead) )
		{
            nFileType = AVS_OFFICESTUDIO_FILE_DOCUMENT_DOC_FLAT; // without compaund container
		}

//------------------------------------------------------------------------------------------------
		file.CloseFile();

		if (buffer)delete []buffer;
		buffer = NULL;
	}
	if (nFileType != AVS_OFFICESTUDIO_FILE_UNKNOWN)return true;
//------------------------------------------------------------------------------------------------
//// by Extension

    std::wstring::size_type nExtPos = fileName.rfind(L'.');
	std::wstring sExt = L"unknown";
    
    if (nExtPos != std::wstring::npos)
        sExt = fileName.substr(nExtPos);

	std::transform(sExt.begin(), sExt.end(), sExt.begin(), tolower);

    if (0 == sExt.compare(L".mht"))
		nFileType = AVS_OFFICESTUDIO_FILE_DOCUMENT_MHT;
    else if (0 == sExt.compare(L".csv"))
		nFileType = AVS_OFFICESTUDIO_FILE_SPREADSHEET_CSV;
    else if (0 == sExt.compare(L".html") || 0 == sExt.compare(L".htm"))
		nFileType = AVS_OFFICESTUDIO_FILE_DOCUMENT_HTML;
    else if (0 == sExt.compare(L".bin")) //base64 string
		nFileType = AVS_OFFICESTUDIO_FILE_CANVAS_PDF;
    else if (0 == sExt.compare(L".doct"))//случай архива с html viewer
		nFileType = AVS_OFFICESTUDIO_FILE_TEAMLAB_DOCY;
    else //if (0 == sExt.compare(L".txt") || 0 == sExt.compare(L".xml")) //volsciv.rtf -или любой другой
        nFileType = AVS_OFFICESTUDIO_FILE_DOCUMENT_TXT;

	if (nFileType != AVS_OFFICESTUDIO_FILE_UNKNOWN) return true;

	return false;
}