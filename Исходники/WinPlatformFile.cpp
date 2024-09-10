bool C_File::Seek(long long val, SeekMode mode, long long* newdest)
{
	if(m_handle!=INVALID_HANDLE_VALUE) 
	{
		LARGE_INTEGER dest, ndest;
		ndest.QuadPart = 0;
		dest.QuadPart = val;

		unsigned int mmode = 0;
		if(mode==Seek_Set) mmode = FILE_BEGIN;
		else if(mode==Seek_Current) mmode = FILE_CURRENT;
		else if(mode==Seek_End) mmode = FILE_END;

		if(SetFilePointerEx(m_handle, dest, &ndest, mmode))
		{
			if(newdest!=0) *newdest = ndest.QuadPart;
			return true;
		}
	}
	return false;
}