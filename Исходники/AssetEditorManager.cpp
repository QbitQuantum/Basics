bool FAssetEditorManager::CloseAllAssetEditors()
{
	bool bAllEditorsClosed = true;
	for (TMultiMap<IAssetEditorInstance*, UObject*>::TIterator It(OpenedEditors); It; ++It)
	{
		IAssetEditorInstance* Editor = It.Key();
		if (Editor != NULL)
		{
			if ( !Editor->CloseWindow() )
			{
				bAllEditorsClosed = false;
			}
		}
	}

	return bAllEditorsClosed;
}