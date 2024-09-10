/*
 * This is a plain way to read file header.
 * User needs to take care of concurrency issue etc.
 * Parameters :
 *	fn : full name of a database file.
 *	header: Pointer to database file header structure (may not be in shared memory)
 *	len: size of header (may be just SGMNT_HDR_LEN or SIZEOF_FILE_HDR_MAX)
 */
boolean_t file_head_read(char *fn, sgmnt_data_ptr_t header, int4 len)
{
	int 		save_errno, fd, header_size;
	struct stat	stat_buf;

	error_def(ERR_DBFILOPERR);
	error_def(ERR_DBNOTGDS);

	header_size = sizeof(sgmnt_data);
	OPENFILE(fn, O_RDONLY, fd);
	if (-1 == fd)
	{
		save_errno = errno;
		gtm_putmsg(VARLSTCNT(5) ERR_DBFILOPERR, 2, LEN_AND_STR(fn), save_errno);
		return FALSE;
	}
	FSTAT_FILE(fd, &stat_buf, save_errno);
	if (-1 == save_errno)
	{
		save_errno = errno;
		gtm_putmsg(VARLSTCNT(5) ERR_DBFILOPERR, 2, LEN_AND_STR(fn), save_errno);
 		CLOSEFILE(fd, save_errno);
		return FALSE;
	}
	if (!S_ISREG(stat_buf.st_mode) || stat_buf.st_size < header_size)
	{
		gtm_putmsg(VARLSTCNT(4) ERR_DBNOTGDS, 2, LEN_AND_STR(fn));
 		CLOSEFILE(fd, save_errno);
		return FALSE;
	}
	LSEEKREAD(fd, 0, header, header_size, save_errno);
	if (0 != save_errno)
	{
		gtm_putmsg(VARLSTCNT(5) ERR_DBFILOPERR, 2, LEN_AND_STR(fn), save_errno);
 		CLOSEFILE(fd, save_errno);
		return FALSE;
	}
	if (memcmp(header->label, GDS_LABEL, GDS_LABEL_SZ - 1))
	{
		gtm_putmsg(VARLSTCNT(4) ERR_DBNOTGDS, 2, LEN_AND_STR(fn));
 		CLOSEFILE(fd, save_errno);
		return FALSE;
	}
	CHECK_DB_ENDIAN(header, strlen(fn), fn);
	assert(MASTER_MAP_SIZE_MAX >= MASTER_MAP_SIZE(header));
	assert(SGMNT_HDR_LEN == len || SIZEOF_FILE_HDR(header) <= len);
	if (SIZEOF_FILE_HDR(header) <= len)
	{
		LSEEKREAD(fd, ROUND_UP(SGMNT_HDR_LEN + 1, DISK_BLOCK_SIZE), MM_ADDR(header), MASTER_MAP_SIZE(header), save_errno);
		if (0 != save_errno)
		{
			gtm_putmsg(VARLSTCNT(5) ERR_DBFILOPERR, 2, LEN_AND_STR(fn), save_errno);
			CLOSEFILE(fd, save_errno);
			return FALSE;
		}
	}
	CLOSEFILE(fd, save_errno);
	if (0 != save_errno)
	{
		gtm_putmsg(VARLSTCNT(5) ERR_DBFILOPERR, 2, LEN_AND_STR(fn), save_errno);
		return FALSE;
	}
	return TRUE;
}