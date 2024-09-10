int
meta_load_sysindex(char *sysindex)
{
	int	fd;
	char	tab_meta_dir[TABLE_NAME_MAX_LEN];
	int	status;
	int	rtn_stat;


	rtn_stat= TRUE;
	
	
	MEMSET(tab_meta_dir, 256);
	MEMCPY(tab_meta_dir, MT_META_INDEX, STRLEN(MT_META_INDEX));
	str1_to_str2(tab_meta_dir, '/', "sysindex");

	OPEN(fd, tab_meta_dir, (O_RDONLY));

	if (fd < 0)
	{
		return FALSE;
	}

	status = READ(fd, sysindex, sizeof(META_SYSINDEX));

	Assert(status == sizeof(META_SYSINDEX));

	if (status != sizeof(META_SYSINDEX))
	{
		traceprint("Save sysindex hit error!\n");
		rtn_stat = FALSE;
		
	}

	CLOSE(fd);

	return rtn_stat;
}