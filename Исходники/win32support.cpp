//-----------------------------------------------------------------------------
IPlatformBitmap* IPlatformBitmap::createFromMemory (const void* ptr, uint32_t memSize)
{
#ifdef __GNUC__
	typedef IStream* (*SHCreateMemStreamProc) (const BYTE* pInit, UINT cbInit);
	HMODULE shlwDll = LoadLibraryA ("shlwapi.dll");
	SHCreateMemStreamProc proc = reinterpret_cast<SHCreateMemStreamProc> (GetProcAddress (shlwDll, MAKEINTRESOURCEA (12)));
	IStream* stream = proc (static_cast<const BYTE*> (ptr), memSize);
#else
	IStream* stream = SHCreateMemStream ((const BYTE*)ptr, memSize);
#endif
	if (stream)
	{
#if VSTGUI_DIRECT2D_SUPPORT
		if (getD2DFactory ())
		{
			D2DBitmap* result = new D2DBitmap ();
			if (result->loadFromStream (stream))
			{
				stream->Release ();
				return result;
			}
			stream->Release ();
			result->forget ();
			return 0;
		}
#endif
		GdiplusBitmap* bitmap = new GdiplusBitmap ();
		if (bitmap->loadFromStream (stream))
		{
			stream->Release ();
			return bitmap;
		}
		bitmap->forget ();
		stream->Release ();
	}
#ifdef __GNUC__
	FreeLibrary (shlwDll);
#endif
	return 0;
}