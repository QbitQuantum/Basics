//======================================
// Global Functions
//======================================
void FillBehaviorPackageList( void )
{
	Script script;
	const char	*token;
	char  *buf;
	BehaviorPackageType_t *packageType;
	
	// Check if we even HAVE a BehaviorPackages.txt file
	if ( gi.FS_ReadFile( "global/BehaviorPackages.txt", ( void ** )&buf, true ) == -1 )
		return;
	
	script.LoadFile( "global/BehaviorPackages.txt" );
	
	if ( script.length < 0 )
		return;
	
	
	while ( script.TokenAvailable ( true ) )
	{
		token = script.GetToken(false);
		
		if (!Q_stricmp( token , "Package" ) )
		{
			packageType = 0;
			packageType = new BehaviorPackageType_t;
			
			if ( !packageType )
				gi.Error( ERR_FATAL, "FillBehaviorPackageList -- could not create packageType" );
			
			//Set the name and file
			packageType->packageName = script.GetToken(false);
			packageType->stateFile   = script.GetToken(false);
			
			PackageList.AddObject( packageType );
			
		}
		
	}
	
	script.Close();
}