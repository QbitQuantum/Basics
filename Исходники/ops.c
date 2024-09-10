int jg_getattr(const char *path, struct stat *buf) {
	struct jgfs_dir_clust *parent;
	struct jgfs_dir_ent   *child;
	int rtn;
	if ((rtn = jgfs_lookup(path, &parent, &child)) != 0) {
		return rtn;
	}
	
	buf->st_nlink = 1;
	buf->st_uid = 0;
	buf->st_gid = 0;
	buf->st_size = child->size;
	buf->st_blocks = CEIL(child->size, jgfs_clust_size());
	buf->st_atime = buf->st_ctime = buf->st_mtime = child->mtime;
	
	if (child->type == TYPE_FILE) {
		buf->st_mode = 0644 | S_IFREG;
	} else if (child->type == TYPE_DIR) {
		buf->st_mode = 0755 | S_IFDIR;
	} else if (child->type == TYPE_SYMLINK) {
		buf->st_mode = 0777 | S_IFLNK;
	} else {
		errx(1, "jg_getattr: unknown type 0x%x", child->type);
	}
	
	return 0;
}