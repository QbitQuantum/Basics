//
// Retrieve the texture info of the active sender
// - redundancy 
bool spoutSenderNames::FindActiveSender(char sendername[SpoutMaxSenderNameLen], unsigned int &theWidth, unsigned int &theHeight, HANDLE &hSharehandle, DWORD &dwFormat)
{
    SharedTextureInfo TextureInfo;
	char sname[SpoutMaxSenderNameLen];

    if(GetActiveSender(sname)) { // there is an active sender
		if(getSharedInfo(sname, &TextureInfo)) {
			strcpy_s(sendername, SpoutMaxSenderNameLen, sname); // pass back sender name
			theWidth        = (unsigned int)TextureInfo.width;
			theHeight       = (unsigned int)TextureInfo.height;
#ifdef _M_X64
			hSharehandle = (HANDLE)(LongToHandle((long)TextureInfo.shareHandle));
#else
			hSharehandle = (HANDLE)TextureInfo.shareHandle;
#endif
			// hSharehandle	= (HANDLE)TextureInfo.shareHandle;
			dwFormat        = (DWORD)TextureInfo.format;
			return true;
		}
	}

    return false;

} // end FindActiveSender