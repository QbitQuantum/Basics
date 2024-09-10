/*
	リンクの解決
	あらかじめ、CoInitialize(NULL); を実行しておくこと
*/
BOOL ReadLinkU8(LPCSTR src, LPSTR dest, LPSTR arg)
{
	IShellLink		*shellLink;
	IPersistFile	*persistFile;
	WCHAR			wbuf[MAX_PATH];
	BOOL			ret = FALSE;

	if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW,
		(void **)&shellLink)))
	{
		if (SUCCEEDED(shellLink->QueryInterface(IID_IPersistFile, (void **)&persistFile)))
		{
			U8toW(src, wbuf, wsizeof(wbuf));
			if (SUCCEEDED(persistFile->Load(wbuf, STGM_READ)))
			{
				if (SUCCEEDED(shellLink->GetPath((char *)wbuf, MAX_PATH, NULL, SLGP_SHORTPATH)))
				{
					WtoU8(wbuf, dest, MAX_PATH_U8);
					shellLink->GetArguments((char *)wbuf, MAX_PATH);
					WtoU8(wbuf, arg, MAX_PATH_U8);
					ret = TRUE;
				}
			}
			persistFile->Release();
		}
		shellLink->Release();
	}
	return	ret;
}