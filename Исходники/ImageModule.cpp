void KImageModule::Unload(void)
{
    SymUnloadModule(m_hProcess, m_symbolbase);
    SymCleanup(m_hProcess);

	if ( m_image.ModuleName )
		UnMapAndLoad(& m_image);
} 