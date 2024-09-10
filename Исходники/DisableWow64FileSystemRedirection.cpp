DisableWow64FileSystemRedirection::~DisableWow64FileSystemRedirection(void)
{
	if (m_hModule)
	{
		Wow64DisableWow64FsRedirection("Wow64RevertWow64FsRedirection");
		::FreeLibrary(m_hModule);
	}
}