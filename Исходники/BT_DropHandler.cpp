void DropHandler::RevokeHandler()
{
	// revoke 
	if (_isRegistered)
	{
		RevokeDragDrop(_dropWindow);
		_isRegistered = false;
	}

	if (_workingDirectoryDropTarget)
	{
		LOG(QString_NT("Registering Drop Target"));
		_workingDirectoryDropTarget->Release();
	}
}