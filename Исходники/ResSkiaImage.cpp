static void GDIPlusDecoder(CStdValVector* data) {
	HGLOBAL hMem = ::GlobalAlloc(GMEM_FIXED, data->m_data->getLength());
	BYTE* pMem = (BYTE*)::GlobalLock(hMem);
	memcpy(pMem, data->m_data->getMemoryBase(), data->m_data->getLength());

	IStream* pIStream = 0;
	::CreateStreamOnHGlobal(hMem, FALSE, &pIStream);

	Gdiplus::Bitmap* pImgBitmap = Gdiplus::Bitmap::FromStream(pIStream);

	InitClsids();

	pIStream->Release();
	HRESULT hr = ::CreateStreamOnHGlobal(NULL, true, &pIStream);

	pImgBitmap->Save(pIStream, &s_bmpClsid, NULL);

	LARGE_INTEGER liTemp = {0};
	pIStream->Seek(liTemp, STREAM_SEEK_SET, NULL);
	
	STATSTG stats = {0};
	pIStream->Stat(&stats, 0);
	DWORD dwSize = (DWORD)stats.cbSize.QuadPart;

	delete data->m_data;
	data->m_data = new SkMemoryStream(dwSize);
	pIStream->Read((void *)data->m_data->getMemoryBase(), dwSize, NULL);

	::GlobalUnlock(hMem);
	::GlobalFree(hMem);
	pIStream->Release();

	delete pImgBitmap;
}