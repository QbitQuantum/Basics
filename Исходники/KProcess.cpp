bool KProcess::saveFile(const char *dir,const char *unix_file)
{
	std::stringstream s;
	s << dir << "kp_" << getpid() << "_" << getProcessId() << "_" << sig;
	kassert(file==NULL);
	file = strdup(s.str().c_str());
	KFile fp;
	if (fp.open(file,fileWrite)) {
		if (unix_file) {
			fp.fprintf("%s",unix_file);
		}
		return true;
	} else {
		free(file);
		file = NULL;
		return false;
	}
}