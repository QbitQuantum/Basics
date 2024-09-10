s32 cellFsFstat(u32 fd, vm::ptr<CellFsStat> sb)
{
	cellFs.trace("cellFsFstat(fd=0x%x, sb=*0x%x)", fd, sb);

	// call the syscall
	return sys_fs_fstat(fd, sb);
}