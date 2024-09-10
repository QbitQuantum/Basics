int trunk_binlog_compress_rollback()
{
	int result;
	int rollback_fd;
	char binlog_filename[MAX_PATH_SIZE];
	char rollback_filename[MAX_PATH_SIZE];
	struct stat fs;

	get_trunk_binlog_filename(binlog_filename);
	get_trunk_rollback_filename(rollback_filename);
	if (trunk_binlog_fd < 0)
	{
		if (access(rollback_filename, F_OK) == 0)
		{
			if (rename(rollback_filename, binlog_filename) != 0)
			{
				result = errno != 0 ? errno : EPERM;
				logError("file: "__FILE__", line: %d, "\
					"rename %s to %s fail, " \
					"errno: %d, error info: %s",
					__LINE__, rollback_filename,
					binlog_filename, result,
					STRERROR(result));
				return result;
			}
		}

		return 0;
	}

	if (stat(rollback_filename, &fs) != 0)
	{
		result = errno != 0 ? errno : ENOENT;
		if (result == ENOENT)
		{
			return 0;
		}
		logError("file: "__FILE__", line: %d, " \
			"stat file %s fail, errno: %d, error info: %s",
			__LINE__, rollback_filename,
			result, STRERROR(result));
		return result;
	}

	if (fs.st_size == 0)
	{
		unlink(rollback_filename);  //delete zero file directly
		return 0;
	}

	if ((result=trunk_binlog_close_writer(true)) != 0)
	{
		return result;
	}

	if ((rollback_fd=trunk_binlog_open_read(rollback_filename,
		false)) < 0)
	{
		return errno != 0 ? errno : ENOENT;
	}

	result = trunk_binlog_merge_file(rollback_fd);
	close(rollback_fd);
	if (result == 0)
	{
		if (unlink(rollback_filename) != 0)
		{
			result = errno != 0 ? errno : EPERM;
			logWarning("file: "__FILE__", line: %d, " \
				"unlink %s fail, " \
				"errno: %d, error info: %s",
				__LINE__, rollback_filename,
				result, STRERROR(result));
		}

		return trunk_binlog_open_writer(binlog_filename);
	}
	else
	{
		trunk_binlog_open_writer(binlog_filename);
		return result;
	}
}