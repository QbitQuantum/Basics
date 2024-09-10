//
// Write the 'disconnectAttr' statements for those connections which were
// made in referenced files, but broken in the main scene.
//
void maTranslator::writeBrokenRefConnections(fstream& f)
{
	unsigned int	numBrokenConnections = fBrokenConnSrcs.length();
	unsigned int	i;

	for (i = 0; i < numBrokenConnections; i++)
	{
		f << "disconnectAttr \""
		  << fBrokenConnSrcs[i].partialName(true).asChar()
		  << "\" \""
		  << fBrokenConnDests[i].partialName(true).asChar()
		  << "\"";

		//
		// If the destination plug is a multi for which index does not
		// matter, then we must add a "-na/nextAvailable" flag to the
		// command.
		//
		MObject			attr = fBrokenConnDests[i].attribute();
		MFnAttribute	attrFn(attr);

		if (!attrFn.indexMatters()) f << " -na";

		f << ";" << endl;
	}
}