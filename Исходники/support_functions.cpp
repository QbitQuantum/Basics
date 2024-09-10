bool is_exist(string filename) {
	struct stat buf;
	int result = stat(filename.c_str(), &buf);
	return (result==0);
}