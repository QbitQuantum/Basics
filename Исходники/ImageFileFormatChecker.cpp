bool CImageFileFormatChecker::isImageFile(std::wstring& fileName)
{
	eFileType  = _CXIMAGE_FORMAT_UNKNOWN;
///////////////////////////////////////////////////////////////////////////////	
	NSFile::CFileBinary file;
	if (!file.OpenFile(fileName))
		return false;

	BYTE* buffer = new BYTE[MIN_SIZE_BUFFER];
	if (!buffer)
		return false;

	DWORD sizeRead = 0;
	if (!file.ReadFile(buffer, MIN_SIZE_BUFFER, sizeRead))
	{
		delete []buffer;
		return false;
	}
	file.CloseFile();
/////////////////////////////////////////////////////////////////////////////////
	if (isBmpFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_BMP;
	}
	if (isGifFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_GIF;
	}
	if (isPngFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_PNG;
	}
	if (isTgaFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_TGA;
	}
	if (isPcxFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_PCX;
	}	
	if (isJpgFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_JPG;
	}
	if (isEmfFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_EMF;
	}
	if (isWmfFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_WMF;
	}
	if (isTiffFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_TIF;
	}	
	if (isIcoFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_ICO;
	}
	if (isWbFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_WB;
	}	
	if (isPsdFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_PSD;
	}
	if (isRasFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_RAS;
	}	

	if (isIpodFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_UNKNOWN;
	}
	if (isJ2kFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_JP2;
	}
	if (isJp2File(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_JP2;
	}
	if (isMj2File(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_JP2;
	}
	if (isSfwFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_UNKNOWN;
	}
	if (isSvmFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_UNKNOWN;
	}
	if (isSwfFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_UNKNOWN;
	}
	if (isWbcFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_UNKNOWN;
	}	
	if (isWbzFile(buffer,sizeRead))
	{
		eFileType = _CXIMAGE_FORMAT_UNKNOWN;
	}	
///////////////////////////////////////////////////////////////////////
	if (isSvgFile(fileName))
	{
		eFileType = _CXIMAGE_FORMAT_UNKNOWN;
	}	
	if (isRawFile(fileName))
	{
		eFileType = _CXIMAGE_FORMAT_UNKNOWN;
	}
///////////////////////////////////////////////////////////////////////
	delete [] buffer;

	if (eFileType)return true;
	return false;
}