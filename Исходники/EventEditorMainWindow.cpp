/*!	\brief		Creates and initializes the file panels.
 *	
 */
void 	EventEditorMainWindow::InitializeFilePanels( BString path )
{
	BPath eventualDirectoryPath;
	BPath pathToFile;
	bool	initToDefaults = false;
	BDirectory parentDirectory, eventualDirectory;
	status_t	status;

	// Initializing from a submitted path	
	do {
		if ( path != BString("") ) {
			pathToFile.SetTo( path.String() );
			if ( ( pathToFile.InitCheck() != B_OK ) ||
			 	  ( pathToFile.GetParent( &eventualDirectoryPath ) != B_OK ) ||
			 	  ( eventualDirectory.SetTo( eventualDirectoryPath.Path() ) != B_OK ) )
			{
				initToDefaults = true;
				break;	// Go to after "while"
			}
		}
		else
		{
			initToDefaults = true;
		}
	} while ( false );
	
	// Else, initialize to defaults
	if ( initToDefaults )
	{
		find_directory( B_USER_DIRECTORY,
						 &eventualDirectoryPath,
						 true );	// Useless flag - system can't boot without "home"
		parentDirectory.SetTo( eventualDirectoryPath.Path() );
		status = parentDirectory.CreateDirectory( "events", &eventualDirectory );
		if ( status == B_FILE_EXISTS ) {
			eventualDirectory.SetTo( &parentDirectory, "events" );
			status = eventualDirectory.InitCheck();
		}
		if ( status != B_OK )
		{
			global_toReturn = ( uint32 )status;
			be_app->PostMessage( B_QUIT_REQUESTED );
		}
	} // <-- end of setting default directories
	
	
	// At this point, eventualDirectory is set to the directory where files
	// should be stored.
	
	BEntry entry;
	entry_ref ref;
	eventualDirectory.GetEntry( &entry );
	entry.GetRef( &ref );

	// Construct file panels
	fOpenFile = new BFilePanel( B_OPEN_PANEL,
										 new BMessenger( Looper(), this ),
										 &ref,
										 B_FILE_NODE,
										 false,
										 new BMessage( kFileOpenConfirmed ),
										 fRefFilter );

	fSaveFile = new BFilePanel( B_SAVE_PANEL,
										 new BMessenger( Looper(), this ),
										 &ref,
										 B_FILE_NODE,
										 false,
										 new BMessage( kFileSaveConfirmed ),
										 fRefFilter );
	entry.Unset();
	if ( !fOpenFile || !fSaveFile ) {
		global_toReturn = ( uint32 )B_NO_MEMORY;
		be_app->PostMessage( B_QUIT_REQUESTED );
	}

}	// <-- end of function EventEditorMainWindow::InitializeFilePanels