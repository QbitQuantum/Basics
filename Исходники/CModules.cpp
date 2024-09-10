bool CModules::Load( const char* strName )
{
	void* pLibrary = LoadModule( (m_strLocation + Holly::Platform::LibraryPretension() + "holly_" + strName + Holly::Platform::LibraryExtension()).c_str() );
	
	if ( !pLibrary ) pLibrary = LoadModule( strName );
	if ( !pLibrary ) return false;

	void* pFunction = Holly::Platform::FindFunction( pLibrary, "Holly_Module_Dynamic" );
	if ( !pFunction )
	{
		Holly::Errors::Add( "Invalid Module" );
		Holly::Platform::FreeLibrary( pLibrary );
		return false;
	}

	Module mod;
		mod.pInstance = pLibrary;
		mod.pModuleQuery = (fnModuleQuery)pFunction;

	m_Modules[ strName ] = mod;

	return true;
}