SbBool
SoTexture2::readImage(const SbString& fname, int &w, int &h, int &nc, 
		      unsigned char *&bytes)
//
////////////////////////////////////////////////////////////////////////
{
    w = h = nc = 0;
    bytes = NULL;
    
    // Empty file means an empty image...
    if (fname.getString()[0] == '\0')
	return TRUE;

    SoInput in;
    if (!in.openFile(fname.getString(), TRUE)) {
	return FALSE;
    }

#ifdef DEBUG
    SoDebugError::postInfo("SoTexture2::readImage",
			   "Reading texture image %s",
			   fname.getString());
#endif

    if (ReadSGIImage(in, w, h, nc, bytes))
	return TRUE;

    // fiopen() closes the file even if it can't read the data, so 
    // reopen it
    in.closeFile();
    if (!in.openFile(fname.getString(), TRUE))
	return FALSE;

    if (ReadGIFImage(in, w, h, nc, bytes))
	return TRUE;

    if (ReadJPEGImage(in, w, h, nc, bytes))
	return TRUE;

    return FALSE;
}