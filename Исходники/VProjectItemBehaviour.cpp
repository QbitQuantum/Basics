XBOX::VError VProjectItemFolder::Rename( const XBOX::VString& inNewName)
{
	if (fOwner == NULL)
		return VE_FOLDER_CANNOT_RENAME;
	
	VFilePath path;
	if (!fOwner->GetFilePath( path))
		return VE_FOLDER_CANNOT_RENAME;

	VFolder *newFolder = NULL;
	VFolder folder( path);
	VError err = folder.Rename( inNewName, &newFolder);
	if (err == VE_OK && newFolder != NULL)
	{
		VString folderName;
		newFolder->GetName( folderName);

		fOwner->SetName( folderName);	// sc 26/09/2011, WAK0073011
		fOwner->SetDisplayName( folderName);
		
		if (fOwner->HasRelativePath())
		{
			folderName += FOLDER_SEPARATOR;
			fOwner->SetRelativePath( folderName);
		}
		else
		{
			VFilePath path;
			newFolder->GetPath( path);
			fOwner->SetURL( VURL( path));
		}
	}

	if (err != VE_OK)
		err = VE_FOLDER_CANNOT_RENAME;
	
	return err;	
}