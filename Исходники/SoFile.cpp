void
SoFile::nameChangedCB(void *data, SoSensor *)
//
////////////////////////////////////////////////////////////////////////
{
    SoFile *f = (SoFile *)data;

    f->children.truncate(0);

    SoInput in;
    const char *filename = f->name.getValue().getString();
    
    // Open file
    f->readOK = TRUE;
    if (! in.openFile(filename, TRUE)) {
	f->readOK = FALSE;
	SoReadError::post(&in, "Can't open included file \"%s\" in File node",
			  filename);
    }

    if (f->readOK) {
	SoNode	*node;

	// Read children from opened file.

	while (TRUE) {
	    if (SoDB::read(&in, node)) {
		if (node != NULL)
		    f->children.append(node);
		else
		    break;
	    }
	    else
		f->readOK = FALSE;
	}
	in.closeFile();
    }
    // Note: if there is an error reading one of the children, the
    // other children will still be added properly...
}