int cellFsReaddir(u32 fd, mem_ptr_t<CellFsDirent> dir, mem64_t nread)
{
	sys_fs.Log("cellFsReaddir(fd=%d, dir_addr=0x%x, nread_addr=0x%x)", fd, dir.GetAddr(), nread.GetAddr());

	vfsDirBase* directory;
	if(!sys_fs.CheckId(fd, directory))
		return CELL_ESRCH;
	if(!dir.IsGood() || !nread.IsGood())
		return CELL_EFAULT;

	const DirEntryInfo* info = directory->Read();
	if(info)
	{
		nread = 1;
		Memory.WriteString(dir.GetAddr()+2, info->name.wx_str());
		dir->d_namlen = info->name.Length();
		dir->d_type = (info->flags & DirEntry_TypeFile) ? CELL_FS_TYPE_REGULAR : CELL_FS_TYPE_DIRECTORY;
	}
	else
	{
		nread = 0;
	}

	return CELL_OK;
}