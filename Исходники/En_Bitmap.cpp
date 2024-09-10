IPicture* CEn_Bitmap::LoadFromBuffer(BYTE* pBuff, int nSize)
{
	IPicture* pPicture = NULL;

	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nSize);
	if (hGlobal != NULL)
	{
		void* pData = GlobalLock(hGlobal);
		if (pData != NULL)
		{
			memcpy(pData, pBuff, nSize);
			GlobalUnlock(hGlobal);

			IStream* pStream = NULL;
			if (CreateStreamOnHGlobal(hGlobal, TRUE/*fDeleteOnRelease*/, &pStream) == S_OK)
			{
				// Not sure what the 'KeepOriginalFormat' property is really used for. But if 'OleLoadPicture'
				// is invoked with 'fRunmode=FALSE' the function always creates a temporary file which even
				// does not get deleted when all COM pointers were released. It eventually gets deleted only
				// when process terminated. Using 'fRunmode=TRUE' does prevent this behaviour and does not
				// seem to have any other side effects.
				VERIFY( OleLoadPicture(pStream, nSize, TRUE/*FALSE*/, IID_IPicture, (LPVOID*)&pPicture) == S_OK );
				pStream->Release();
			}
			else
				GlobalFree(hGlobal);
		}
		else
			GlobalFree(hGlobal);
	}

	return pPicture; // caller releases
}