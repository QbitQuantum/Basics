//There is no creation time on Linux, but there is a status change time (modification of file's inode).
VError XLinuxFile::GetTimeAttributes(VTime* outLastModification, VTime* outLastStatusChange, VTime* outLastAccess) const
{
	StatHelper statHlp;
	VError verr=statHlp.Stat(fPath);

	if(verr!=VE_OK)
		return verr;

	if(outLastAccess!=NULL)
		outLastAccess->FromTime(statHlp.GetLastAccess());

	if(outLastModification!=NULL)
		outLastModification->FromTime(statHlp.GetLastModification());

	if(outLastStatusChange!=NULL)
		outLastStatusChange->FromTime(statHlp.GetLastStatusChange());

    return VE_OK;
}