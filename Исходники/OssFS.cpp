int OssFS::open(const char *path, struct fuse_file_info *fileInfo) 
{
	log_debug("path:[%s]", path);
	OssObject *obj = this->find_certain_path(path);
	
	if (obj != NULL) {
		return obj->fopen(fileInfo);
	} else
		return -ENOENT;
}