MStatus uninitializePlugin( MObject obj)
{
	MStatus   status;
	MFnPlugin plugin( obj );

	// Loop through all the ids and remove the callbacks
	//
	int i;
	int len = eventNames.length();

	for (i = 0; i < len; ++i)
	{
		if (callbackId[i] != 0)
		{
			MGlobal::displayWarning("Removing callback for " +
									eventNames[i] +
									"\n");
			MMessage::removeCallback(callbackId[i]);
			callbackId[i] = 0;
		}
	}

	eventNames.clear();

	delete [] callbackId;

	// Deregister the command
	//
	status = plugin.deregisterCommand("eventTest");

	if (!status)
	{
		status.perror("deregisterCommand");
	}

	return status;
}