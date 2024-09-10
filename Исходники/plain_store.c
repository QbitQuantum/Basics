int default_create_and_write(uint64_t oid, const struct siocb *iocb)
{
	char path[PATH_MAX], tmp_path[PATH_MAX];
	int flags = prepare_iocb(oid, iocb, true);
	int ret, fd;
	uint32_t len = iocb->length;
	size_t obj_size;

	sd_debug("%"PRIx64, oid);
	get_store_path(oid, iocb->ec_index, path);
	get_store_tmp_path(oid, iocb->ec_index, tmp_path);
	fd = open(tmp_path, flags, sd_def_fmode);
	if (fd < 0) {
		if (errno == EEXIST) {
			/*
			 * This happens if node membership changes during object
			 * creation; while gateway retries a CREATE request,
			 * recovery process could also recover the object at the
			 * same time.  They should try to write the same date,
			 * so it is okay to simply return success here.
			 */
			sd_debug("%s exists", tmp_path);
			return SD_RES_SUCCESS;
		}

		sd_err("failed to open %s: %m", tmp_path);
		return err_to_sderr(path, oid, errno);
	}

	obj_size = get_store_objsize(oid);
	ret = prealloc(fd, obj_size);
	if (ret < 0) {
	          ret = err_to_sderr(path, oid, errno);
		  goto out;
	}

	ret = xpwrite(fd, iocb->buf, len, iocb->offset);
	if (ret != len) {
		sd_err("failed to write object. %m");
		ret = err_to_sderr(path, oid, errno);
		goto out;
	}

	/*
	 * Modern FS like ext4, xfs defaults to automatic syncing of files after
	 * replace-via-rename and replace-via-truncate operations. So rename
	 * without fsync() is actually safe.
	 */
	ret = rename(tmp_path, path);
	if (ret < 0) {
		sd_err("failed to rename %s to %s: %m", tmp_path, path);
		ret = err_to_sderr(path, oid, errno);
		goto out;
	}

	ret = SD_RES_SUCCESS;
	objlist_cache_insert(oid);
out:
	if (ret != SD_RES_SUCCESS && unlink(tmp_path) != 0)
		sd_err("failed to unlink %s: %m", tmp_path);
	close(fd);
	return ret;
}