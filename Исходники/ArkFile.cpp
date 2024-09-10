// from a given offset into an ark, the correct file handle is returned
// which is pointing at the correct offset in that file
// (will seek to a new offset outside of current bounds)
// 
// args:	offset into ark
//			flag or whether to seek outside existing file sizes
// returns:	file handle if successful
//			NULL if error
FILE* ArkFile::GetHandleFromOffset(s64 offset, bool offsetMustExist)
{
	s64 filesize;
	for(int i=0; i<(int)mArkHandles.size(); i++)
	{
		if((filesize=GetFilesize(mArkHandles[i])) < 0)
			return NULL;
		if(offset >= filesize)
		{
			// if there is still another ark file after this one
			// then update the offset to be in that ark file
			if(i+1 < (int)mArkHandles.size())
				offset -= filesize;
			else
				break;
		}
		else
		{
			FSEEK64(mArkHandles[i], offset, SEEK_SET);
			return mArkHandles[i];
		}
	}
	
	// offset is outside of the current file space
	if(offsetMustExist)
		return NULL;
	
	// check if we need to open a new ark file
	char zero[1] = {0};
	FILE* fd = NULL;
	if(offset >= mMaxArkSize &&
		mMaxArkSize != 0)
	{
		// pad the current ark file up to the max ark size limit,
		// then create a new ark file and seek to the required offset in it
		fd = mArkHandles[mArkHandles.size()-1];
		FSEEK64(fd, 0, SEEK_END);
		if(FTELL64(fd) < mMaxArkSize)
		{
			FSEEK64(fd, mMaxArkSize-1, SEEK_SET);
			fwrite(zero, 1, 1, fd);
		}
		offset -= mMaxArkSize;
		char new_filename[260];
		sprintf(new_filename, "%s%cMAIN_%d.ARK", mDirname, DIRSEPCHAR, (int) mArkHandles.size());
		FILE* fd = fopen(new_filename, "w+b");
		if(fd == NULL)
			return NULL;
		mArkHandles.push_back(fd);
		if(offset > 0)
		{
			FSEEK64(fd, offset-1, SEEK_SET);
			fwrite(zero, 1, 1, fd);
		}
		return fd;
	}
	else
	{
		// according to posix specifications, an fseek followed by an fwrite
		// should make a file grow to the new end of file mark.
		// (check the file needs to grow first though)
		fd = mArkHandles[mArkHandles.size()-1];
		FSEEK64(fd, 0, SEEK_END);
		if(FTELL64(fd) < offset)
		{
			FSEEK64(fd, offset-1, SEEK_SET);
			fwrite(zero, 1, 1, fd);
		}
		else
		{
			FSEEK64(fd, offset, SEEK_SET);
		}
		return fd;
	}
}