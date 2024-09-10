//Function called by filesystems to fill readdir entry
static int readDirFiller(void * buf, unsigned int iNode, const char * name, int len)
{
	//Called to fill buffer
	ReadDirFillerBuf * rdBuffer = (ReadDirFillerBuf *) buf;
	IoReadDirEntry * entry = rdBuffer->nextEntry;

	//If count is 0, overflow
	if(rdBuffer->count == 0)
	{
		return -EINVAL;
	}

	//Basic memory checks
	if(!MemCommitForWrite(entry, sizeof(IoReadDirEntry)))
	{
		return -EFAULT;
	}

	//Fill info
	entry->iNode = iNode;
	if(len > 255)
	{
		len = 255;
	}

	MemCpy(entry->name, name, len);
	entry->name[len] = '\0';

	//Move to next entry
	rdBuffer->nextEntry++;
	rdBuffer->count--;
	return 0;
}