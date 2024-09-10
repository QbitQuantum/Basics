static int storage_trunk_load()
{
#define TRUNK_DATA_FIELD_COUNT  6
#define TRUNK_LINE_MAX_LENGHT  64

	int64_t restore_offset;
	char trunk_data_filename[MAX_PATH_SIZE];
	char buff[4 * 1024 + 1];
	int line_count;
	char *pLineStart;
	char *pLineEnd;
	char *cols[TRUNK_DATA_FIELD_COUNT];
	FDFSTrunkFullInfo trunkInfo;
	int result;
	int fd;
	int bytes;
	int len;

	snprintf(trunk_data_filename, sizeof(trunk_data_filename), \
		"%s/data/%s", g_fdfs_base_path, STORAGE_TRUNK_DATA_FILENAME);
	if (g_trunk_init_reload_from_binlog)
	{
		if (unlink(trunk_data_filename) != 0)
		{
			result = errno != 0 ? errno : ENOENT;
			if (result != ENOENT)
			{
				logError("file: "__FILE__", line: %d, " \
					"unlink file %s fail, " \
					"errno: %d, error info: %s", __LINE__, \
					trunk_data_filename, result, \
					STRERROR(result));
				return result;
			}
		}

		restore_offset = 0;
		return storage_trunk_restore(restore_offset);
	}

	fd = open(trunk_data_filename, O_RDONLY);
	if (fd < 0)
	{
		result = errno != 0 ? errno : EIO;
		if (result == ENOENT)
		{
			restore_offset = 0;
			return storage_trunk_restore(restore_offset);
		}

		logError("file: "__FILE__", line: %d, " \
			"open file %s fail, " \
			"errno: %d, error info: %s", \
			__LINE__, trunk_data_filename, \
			result, STRERROR(result));
		return result;
	}

	if ((bytes=read(fd, buff, sizeof(buff) - 1)) < 0)
	{
		result = errno != 0 ? errno : EIO;
		logError("file: "__FILE__", line: %d, " \
			"read from file %s fail, " \
			"errno: %d, error info: %s", \
			__LINE__, trunk_data_filename, \
			result, STRERROR(result));
		close(fd);
		return result;
	}

	*(buff + bytes) = '\0';
	pLineEnd = strchr(buff, '\n');
	if (pLineEnd == NULL)
	{
		logError("file: "__FILE__", line: %d, " \
			"read offset from file %s fail", \
			__LINE__, trunk_data_filename);
		close(fd);
		return EINVAL;
	}

	*pLineEnd = '\0';
	restore_offset = strtoll(buff, NULL, 10);
	pLineStart = pLineEnd + 1;  //skip \n
	line_count = 0;
	while (1)
	{
		pLineEnd = strchr(pLineStart, '\n');
		if (pLineEnd == NULL)
		{
			if (bytes < sizeof(buff) - 1) //EOF
			{
				break;
			}

			len = strlen(pLineStart);
			if (len > TRUNK_LINE_MAX_LENGHT)
			{
				logError("file: "__FILE__", line: %d, " \
					"file %s, line length: %d too long", \
					__LINE__, trunk_data_filename, len);
				close(fd);
				return EINVAL;
			}

			memcpy(buff, pLineStart, len);
			if ((bytes=read(fd, buff + len, sizeof(buff) \
					- len - 1)) < 0)
			{
				result = errno != 0 ? errno : EIO;
				logError("file: "__FILE__", line: %d, " \
					"read from file %s fail, " \
					"errno: %d, error info: %s", \
					__LINE__, trunk_data_filename, \
					result, STRERROR(result));
				close(fd);
				return result;
			}

			if (bytes == 0)
			{
				result = ENOENT;
				logError("file: "__FILE__", line: %d, " \
					"file: %s, end of file, expect " \
					"end line", __LINE__, \
					trunk_data_filename);
				close(fd);
				return result;
			}

			bytes += len;
			*(buff + bytes) = '\0';
			pLineStart = buff;
			continue;
		}

		++line_count;
		*pLineEnd = '\0';
		if (splitEx(pLineStart, ' ', cols, TRUNK_DATA_FIELD_COUNT) \
			!= TRUNK_DATA_FIELD_COUNT)
		{
			logError("file: "__FILE__", line: %d, " \
				"file %s, line: %d is invalid", \
				__LINE__, trunk_data_filename, line_count);
			close(fd);
			return EINVAL;
		}

		trunkInfo.path.store_path_index = atoi(cols[0]);
		trunkInfo.path.sub_path_high = atoi(cols[1]);
		trunkInfo.path.sub_path_low = atoi(cols[2]);
		trunkInfo.file.id = atoi(cols[3]);
		trunkInfo.file.offset = atoi(cols[4]);
		trunkInfo.file.size = atoi(cols[5]);
		if ((result=storage_trunk_do_add_space(&trunkInfo)) != 0)
		{
			close(fd);
			return result;
		}

		pLineStart = pLineEnd + 1;  //next line
	}

	close(fd);

	if (*pLineStart != '\0')
	{
		logError("file: "__FILE__", line: %d, " \
			"file %s does not end correctly", \
			__LINE__, trunk_data_filename);
		return EINVAL;
	}

	logDebug("file: "__FILE__", line: %d, " \
		"file %s, line count: %d", \
		__LINE__, trunk_data_filename, line_count);

	return storage_trunk_restore(restore_offset);
}