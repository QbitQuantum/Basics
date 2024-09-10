s32 handleFFSOpen(ipcmessage *msg)
{
	char name[MAX_FILENAME_SIZE];
	char *origname = msg->open.device;

	if ((emulationType == FFS_EMU_NONE) ||
		Strncmp(origname, "/dev/",5) == 0) 
	{
		return handleFFSOpen(msg);
	}

	preappend_nand_dev_name(origname, name);
	return FFS_Open(name, IPC_OPEN_RW);
}