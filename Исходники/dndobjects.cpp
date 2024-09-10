CShellExtensionInterface::~CShellExtensionInterface()
{
	if (m_shellExtension)
	{
		((IUnknown*)m_shellExtension)->Release();
		CoFreeUnusedLibraries();
	}

	if (m_hMapping)
		CloseHandle(m_hMapping);

	if (m_hMutex)
		CloseHandle(m_hMutex);

	if (m_dragDirectory != _T(""))
		RemoveDirectory(m_dragDirectory);
}