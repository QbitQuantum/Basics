LPITEMIDLIST getAbsolutePidlFromAbsFilePath(LPWSTR path)
{
	LPITEMIDLIST pidl = NULL;
	LPITEMIDLIST pidlAbsolute = NULL;

	// namespace extension root (desktop) for parsing path
	LPSHELLFOLDER psfDesktop = NULL;
	if (FAILED(SHGetDesktopFolder(&psfDesktop)))
		return pidl;

	// parse path for absolute PIDL
	if (FAILED(psfDesktop->ParseDisplayName(NULL, NULL, path, NULL, &pidl, NULL)))
		return pidl;

	// get the absolute pidl, do not need to free pidlTemp
	pidlAbsolute = ILClone(pidl);

	// cleanup
	CoTaskMemFree(pidl);
	psfDesktop->Release();

	return pidlAbsolute;
}