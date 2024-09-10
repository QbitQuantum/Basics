ExtensionManager::ExtensionManager( bool bInitAPI )
{
	if( !wglGetCurrentContext() ) 
		return;

	extensions = (char*) glGetString( GL_EXTENSIONS );

	if( bInitAPI )
		InitAPI();
}