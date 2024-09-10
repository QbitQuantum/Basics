int hfs_open(const char* path, struct fuse_file_info* info)
{
	std::cerr << "hfs_open(" << path << ")\n";

	return handle_exceptions([&]() {

		std::shared_ptr<Reader> file;
		std::shared_ptr<Reader>* fh;

		file = g_volume->openFile(path);
		fh = new std::shared_ptr<Reader>(file);

		info->fh = uint64_t(fh);
		return 0;
	});
}