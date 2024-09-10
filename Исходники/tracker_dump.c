int fdfs_dump_tracker_global_vars_to_file(const char *filename)
{
	char buff[16 * 1024];
	char szCurrentTime[32];
	int len;
	int result;
	int fd;
	FDFSGroupInfo **ppGroup;
	FDFSGroupInfo **ppGroupEnd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		logError("file: "__FILE__", line: %d, "
			"open file %s fail, errno: %d, error info: %s",
			__LINE__, filename, errno, STRERROR(errno));
		return errno;
	}

	do
	{
		result = 0;
		formatDatetime(g_current_time, "%Y-%m-%d %H:%M:%S", 
				szCurrentTime, sizeof(szCurrentTime));

		len = sprintf(buff, "\n====time: %s  DUMP START====\n", 
				szCurrentTime);
		WRITE_TO_FILE(fd, buff, len)

		len = fdfs_dump_global_vars(buff, sizeof(buff));
		WRITE_TO_FILE(fd, buff, len)

		len = fdfs_dump_tracker_servers(buff, sizeof(buff));
		WRITE_TO_FILE(fd, buff, len)

		len = fdfs_dump_groups_info(buff, sizeof(buff));
		WRITE_TO_FILE(fd, buff, len)

		len = sprintf(buff, "\ngroup name list:\n");
		WRITE_TO_FILE(fd, buff, len)
		len = 0;
		ppGroupEnd = g_groups.groups + g_groups.count;
		for (ppGroup=g_groups.groups; ppGroup<ppGroupEnd; ppGroup++)
		{
			len += sprintf(buff+len, "\t%s\n", (*ppGroup)->group_name);
		}
		len += sprintf(buff+len, "\n");
		WRITE_TO_FILE(fd, buff, len)

		ppGroupEnd = g_groups.sorted_groups + g_groups.count;
		for (ppGroup=g_groups.sorted_groups; ppGroup<ppGroupEnd; ppGroup++)
		{
			len = sprintf(buff, "\nGroup %d.\n", 
				(int)(ppGroup - g_groups.sorted_groups) + 1);
			WRITE_TO_FILE(fd, buff, len)

			len = fdfs_dump_group_stat(*ppGroup, buff, sizeof(buff));
			WRITE_TO_FILE(fd, buff, len)
		}

		len = sprintf(buff, "\n====time: %s  DUMP END====\n\n", 
				szCurrentTime);
		WRITE_TO_FILE(fd, buff, len)
	} while(0);

	close(fd);

	return result;
}