// Die GetEncoderClsid() Funktion wurde einfach aus der MSDN/PSDK Doku kopiert.
// Zu finden mit dem Suchstring "Retrieving the Class Identifier for an Encoder"
// Sucht zu z.B. 'image/jpeg' den passenden Encoder und liefert dessen CLSID...
int GetEncoderClsid(const wchar_t *format, CLSID *pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes
	UINT j;
	ImageCodecInfo* pImageCodecInfo = NULL;

	GdipGetImageEncodersSize(&num, &size);

	if(size == 0) return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL) return -1;  // Failure

	GdipGetImageEncoders(num, size, pImageCodecInfo);

	for(  j = 0; j < num; ++j  ) {
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 ) {
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}