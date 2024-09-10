HRESULT CTMReceiverOutputPin::GetMediaType(int iPosition, CMediaType *pmt){
	CheckPointer(pmt,E_POINTER);

	CAutoLock cAutoLock(m_pFilter->pStateLock());
	if(iPosition < 0)
	{
		return E_INVALIDARG;
	}
	if(iPosition > 0)
	{
		return VFW_S_NO_MORE_ITEMS;
	}
	VIDEOINFO* pvih = (VIDEOINFO*)pmt->AllocFormatBuffer(sizeof(VIDEOINFO));
	LPBITMAPINFOHEADER lpBitmapInfoHeader = &(pvih->bmiHeader);
	lpBitmapInfoHeader->biSize = sizeof(BITMAPINFOHEADER);
	lpBitmapInfoHeader->biBitCount = 32;
	lpBitmapInfoHeader->biWidth = ((CTMReceiverSrc *)m_pFilter)->GetImageWidth()/4*4;
	lpBitmapInfoHeader->biHeight = ((CTMReceiverSrc *)m_pFilter)->GetImageHeight();
	lpBitmapInfoHeader->biPlanes = 1;
	lpBitmapInfoHeader->biCompression = BI_RGB;
	lpBitmapInfoHeader->biSizeImage = ((CTMReceiverSrc *)m_pFilter)->GetImageWidth() / 4 * 4 * ((CTMReceiverSrc *)m_pFilter)->GetImageHeight() * 4;
	lpBitmapInfoHeader->biXPelsPerMeter = 0;
	lpBitmapInfoHeader->biYPelsPerMeter =0;
	lpBitmapInfoHeader->biClrUsed = 0;
	lpBitmapInfoHeader->biClrImportant = 0;
	pvih->AvgTimePerFrame = m_rtAvgTimePerFrame;
	pmt->SetFormatType(&FORMAT_VideoInfo);
	pmt->SetTemporalCompression(FALSE);

	SetRectEmpty(&(pvih->rcSource)); // we want the whole image area rendered.
	SetRectEmpty(&(pvih->rcTarget)); // no particular destination rectangle

	pmt->SetType(&MEDIATYPE_Video);

	// Work out the GUID for the subtype from the header info.
	const GUID SubTypeGUID = GetBitmapSubtype(&pvih->bmiHeader);
	pmt->SetSubtype(&SubTypeGUID);
	pmt->SetSampleSize(pvih->bmiHeader.biSizeImage);

	return S_OK;

}