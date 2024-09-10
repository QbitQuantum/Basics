int
iop_cp(io_args_t *const args)
{
	const char *const src = args->arg1.src;
	const char *const dst = args->arg2.dst;
	const IoCrs crs = args->arg3.crs;
	const io_confirm confirm = args->confirm;
	const int cancellable = args->cancellable;
	struct stat st;

	char block[BLOCK_SIZE];
	FILE *in, *out;
	size_t nread;
	int error;
	struct stat src_st;
	const char *open_mode = "wb";

	ioeta_update(args->estim, src, dst, 0, 0);

#ifdef _WIN32
	if(is_symlink(src) || crs != IO_CRS_APPEND_TO_FILES)
	{
		DWORD flags;
		int error;
		wchar_t *utf16_src, *utf16_dst;

		flags = COPY_FILE_COPY_SYMLINK;
		if(crs == IO_CRS_FAIL)
		{
			flags |= COPY_FILE_FAIL_IF_EXISTS;
		}
		else if(path_exists(dst, DEREF))
		{
			/* Ask user whether to overwrite destination file. */
			if(confirm != NULL && !confirm(args, src, dst))
			{
				return 0;
			}
		}

		utf16_src = utf8_to_utf16(src);
		utf16_dst = utf8_to_utf16(dst);

		error = CopyFileExW(utf16_src, utf16_dst, &win_progress_cb, args, NULL,
				flags) == 0;

		if(error)
		{
			/* FIXME: use real system error message here. */
			(void)ioe_errlst_append(&args->result.errors, dst, IO_ERR_UNKNOWN,
					"Copy file failed");
		}

		free(utf16_src);
		free(utf16_dst);

		ioeta_update(args->estim, NULL, NULL, 1, 0);

		return error;
	}
#endif

	/* Create symbolic link rather than copying file it points to.  This check
	 * should go before directory check as is_dir() resolves symbolic links. */
	if(is_symlink(src))
	{
		char link_target[PATH_MAX];
		int error;

		io_args_t ln_args = {
			.arg1.path = link_target,
			.arg2.target = dst,
			.arg3.crs = crs,

			.cancellable = cancellable,

			.result = args->result,
		};

		if(get_link_target(src, link_target, sizeof(link_target)) != 0)
		{
			(void)ioe_errlst_append(&args->result.errors, src, IO_ERR_UNKNOWN,
					"Failed to get symbolic link target");
			return 1;
		}

		error = iop_ln(&ln_args);
		args->result = ln_args.result;

		if(error != 0)
		{
			(void)ioe_errlst_append(&args->result.errors, src, IO_ERR_UNKNOWN,
					"Failed to make symbolic link");
			return 1;
		}
		return 0;
	}

	if(is_dir(src))
	{
		(void)ioe_errlst_append(&args->result.errors, src, EISDIR,
				strerror(EISDIR));
		return 1;
	}

	if(os_stat(src, &st) != 0)
	{
		(void)ioe_errlst_append(&args->result.errors, src, errno, strerror(errno));
		return 1;
	}

#ifndef _WIN32
	/* Fifo/socket/device files don't need to be opened, their content is not
	 * accessed. */
	if(S_ISFIFO(st.st_mode) || S_ISSOCK(st.st_mode) || S_ISBLK(st.st_mode) ||
			S_ISCHR(st.st_mode))
	{
		in = NULL;
	}
	else
#endif
	{
		in = os_fopen(src, "rb");
		if(in == NULL)
		{
			(void)ioe_errlst_append(&args->result.errors, src, errno,
					strerror(errno));
			return 1;
		}
	}

	if(crs == IO_CRS_APPEND_TO_FILES)
	{
		open_mode = "ab";
	}
	else if(crs != IO_CRS_FAIL)
	{
		int ec;

		if(path_exists(dst, DEREF))
		{
			/* Ask user whether to overwrite destination file. */
			if(confirm != NULL && !confirm(args, src, dst))
			{
				if(in != NULL && fclose(in) != 0)
				{
					(void)ioe_errlst_append(&args->result.errors, src, errno,
							strerror(errno));
				}
				return 0;
			}
		}

		ec = unlink(dst);
		if(ec != 0 && errno != ENOENT)
		{
			(void)ioe_errlst_append(&args->result.errors, dst, errno,
					strerror(errno));
			if(in != NULL && fclose(in) != 0)
			{
				(void)ioe_errlst_append(&args->result.errors, src, errno,
						strerror(errno));
			}
			return ec;
		}

		/* XXX: possible improvement would be to generate temporary file name in the
		 * destination directory, write to it and then overwrite destination file,
		 * but this approach has disadvantage of requiring more free space on
		 * destination file system. */
	}
	else if(path_exists(dst, DEREF))
	{
		(void)ioe_errlst_append(&args->result.errors, src, EEXIST,
				strerror(EEXIST));
		if(in != NULL && fclose(in) != 0)
		{
			(void)ioe_errlst_append(&args->result.errors, src, errno,
					strerror(errno));
		}
		return 1;
	}

#ifndef _WIN32
	/* Replicate fifo without even opening it. */
	if(S_ISFIFO(st.st_mode))
	{
		if(mkfifo(dst, st.st_mode & 07777) != 0)
		{
			(void)ioe_errlst_append(&args->result.errors, src, errno,
					strerror(errno));
			return 1;
		}
		return 0;
	}

	/* Replicate socket or device file without even opening it. */
	if(S_ISSOCK(st.st_mode) || S_ISBLK(st.st_mode) || S_ISCHR(st.st_mode))
	{
		if(mknod(dst, st.st_mode & (S_IFMT | 07777), st.st_rdev) != 0)
		{
			(void)ioe_errlst_append(&args->result.errors, src, errno,
					strerror(errno));
			return 1;
		}
		return 0;
	}
#endif

	out = os_fopen(dst, open_mode);
	if(out == NULL)
	{
		(void)ioe_errlst_append(&args->result.errors, dst, errno, strerror(errno));
		if(fclose(in) != 0)
		{
			(void)ioe_errlst_append(&args->result.errors, src, errno,
					strerror(errno));
		}
		return 1;
	}

	error = 0;

	if(crs == IO_CRS_APPEND_TO_FILES)
	{
		fpos_t pos;
		/* The following line is required for stupid Windows sometimes.  Why?
		 * Probably because it's stupid...  Won't harm other systems. */
		fseek(out, 0, SEEK_END);
		error = fgetpos(out, &pos) != 0 || fsetpos(in, &pos) != 0;

		if(!error)
		{
			ioeta_update(args->estim, NULL, NULL, 0, get_file_size(dst));
		}
	}

	/* TODO: use sendfile() if platform supports it. */

	while((nread = fread(&block, 1, sizeof(block), in)) != 0U)
	{
		if(cancellable && ui_cancellation_requested())
		{
			error = 1;
			break;
		}

		if(fwrite(&block, 1, nread, out) != nread)
		{
			(void)ioe_errlst_append(&args->result.errors, dst, errno,
					strerror(errno));
			error = 1;
			break;
		}

		ioeta_update(args->estim, NULL, NULL, 0, nread);
	}
	if(nread == 0U && !feof(in) && ferror(in))
	{
		(void)ioe_errlst_append(&args->result.errors, src, errno, strerror(errno));
	}

	if(fclose(in) != 0)
	{
		(void)ioe_errlst_append(&args->result.errors, src, errno, strerror(errno));
	}
	if(fclose(out) != 0)
	{
		(void)ioe_errlst_append(&args->result.errors, dst, errno, strerror(errno));
	}

	if(error == 0 && os_lstat(src, &src_st) == 0)
	{
		error = os_chmod(dst, src_st.st_mode & 07777);
		if(error != 0)
		{
			(void)ioe_errlst_append(&args->result.errors, dst, errno,
					strerror(errno));
		}
	}

	ioeta_update(args->estim, NULL, NULL, 1, 0);

	return error;
}

#ifdef _WIN32

static DWORD CALLBACK win_progress_cb(LARGE_INTEGER total,
		LARGE_INTEGER transferred, LARGE_INTEGER stream_size,
		LARGE_INTEGER stream_transfered, DWORD stream_num, DWORD reason,
		HANDLE src_file, HANDLE dst_file, LPVOID param)
{
	static LONGLONG last_size;

	io_args_t *const args = param;

	const char *const src = args->arg1.src;
	const char *const dst = args->arg2.dst;
	ioeta_estim_t *const estim = args->estim;

	if(transferred.QuadPart < last_size)
	{
		last_size = 0;
	}

	ioeta_update(estim, src, dst, 0, transferred.QuadPart - last_size);

	last_size = transferred.QuadPart;

	if(args->cancellable && ui_cancellation_requested())
	{
		return PROGRESS_CANCEL;
	}

	return PROGRESS_CONTINUE;
}

#endif

/* TODO: implement iop_chown(). */
int iop_chown(io_args_t *const args);

/* TODO: implement iop_chgrp(). */
int iop_chgrp(io_args_t *const args);

/* TODO: implement iop_chmod(). */
int iop_chmod(io_args_t *const args);

int
iop_ln(io_args_t *const args)
{
	const char *const path = args->arg1.path;
	const char *const target = args->arg2.target;
	const int overwrite = args->arg3.crs != IO_CRS_FAIL;

	int result;

#ifdef _WIN32
	char cmd[6 + PATH_MAX*2 + 1];
	char *escaped_path, *escaped_target;
	char base_dir[PATH_MAX + 2];
#endif

#ifndef _WIN32
	result = symlink(path, target);
	if(result != 0 && errno == EEXIST && overwrite && is_symlink(target))
	{
		result = remove(target);
		if(result == 0)
		{
			result = symlink(path, target);
			if(result != 0)
			{
				(void)ioe_errlst_append(&args->result.errors, path, errno,
						strerror(errno));
			}
		}
		else
		{
			(void)ioe_errlst_append(&args->result.errors, target, errno,
					strerror(errno));
		}
	}
	else if(result != 0 && errno != 0)
	{
		(void)ioe_errlst_append(&args->result.errors, target, errno,
				strerror(errno));
	}
#else
	if(!overwrite && path_exists(target, DEREF))
	{
		(void)ioe_errlst_append(&args->result.errors, target, EEXIST,
				strerror(EEXIST));
		return -1;
	}

	if(overwrite && !is_symlink(target))
	{
		(void)ioe_errlst_append(&args->result.errors, target, IO_ERR_UNKNOWN,
				"Target is not a symbolic link");
		return -1;
	}

	escaped_path = shell_like_escape(path, 0);
	escaped_target = shell_like_escape(target, 0);
	if(escaped_path == NULL || escaped_target == NULL)
	{
		(void)ioe_errlst_append(&args->result.errors, target, IO_ERR_UNKNOWN,
				"Not enough memory");
		free(escaped_target);
		free(escaped_path);
		return -1;
	}

	if(GetModuleFileNameA(NULL, base_dir, ARRAY_LEN(base_dir)) == 0)
	{
		(void)ioe_errlst_append(&args->result.errors, target, IO_ERR_UNKNOWN,
				"Failed to find win_helper");
		free(escaped_target);
		free(escaped_path);
		return -1;
	}

	break_atr(base_dir, '\\');
	snprintf(cmd, sizeof(cmd), "%s\\win_helper -s %s %s", base_dir, escaped_path,
			escaped_target);

	result = os_system(cmd);
	if(result != 0)
	{
		(void)ioe_errlst_append(&args->result.errors, target, IO_ERR_UNKNOWN,
				"Running win_helper has failed");
	}

	free(escaped_target);
	free(escaped_path);
#endif

	return result;
}