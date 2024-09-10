MStatus 
uninitializePlugin (MObject obj)
{
	MStatus         status;
	MFnPlugin       plugin (obj);

	status = plugin.deregisterFileTranslator ("rtg");
	if (!status)
	{
		status.perror ("deregisterFileTranslator");
		//return status;
	}

	return status;
}