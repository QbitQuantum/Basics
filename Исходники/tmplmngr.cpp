bool CTemplateManager::GetTemplateFilename( UINT32 ordNumberOfTemplate, String_256* pStrNameOfFile )
{
	// Fill the list with all templates (user local, begin second will over-write system ones)
	CTemplateList		setSortFilename;
	GetTemplateList( &setSortFilename, m_TemplatesPath, false );
	GetTemplateList( &setSortFilename, m_LocalTemplatesPath, true );

	// If the template with ordinal doesn't exist, fail
	if( ordNumberOfTemplate > UINT32(setSortFilename.size()) )
		return false;

	// Get enbry for template
	CTemplateList::iterator iter = setSortFilename.begin();
	for( UINT32 i = 1; i < ordNumberOfTemplate; ++i, ++iter )
	{ /*Do nothing!*/ }

	// Pre-pend the path to the template
	PathName			pathTemplates = iter->second ? m_LocalTemplatesPath : m_TemplatesPath;
	pathTemplates.SetFileNameAndType( iter->first );

	*pStrNameOfFile = pathTemplates.GetPath();
	TRACEUSER( "jlh92", _T("Final(%d) = %s\n"), ordNumberOfTemplate, PCTSTR(*pStrNameOfFile) );

	return true;
}