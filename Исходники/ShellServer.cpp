int ShellServer::rstat(ServerContext& s, const char *path, file_stat_t &st)
{
	map<string, file_stat_t*> files;
	string name = base_name(path);
	string_list_t args;
	string_map_t env = s.getEnv();
	process_io_t io;
	args.push_back(path);
	int status = caller(s, "rstat", args, env, io);
	if (status >= 0)
	{
		if (io.output.length() > 0)
		{
			if ((status = bufferToFileStat(io.output.c_str(), (int) io.output.length(), files, name)) >= 0)
			{
				if (files.size() != 1)
				{
					status = -EINVAL;
				}
				else
				{
					status = 0;
					st = *(files[base_name(path)]);
				}
			}
		}
	}
	if (files.size() > 0)
	{
		for (map<string, file_stat_t*>::iterator it = files.begin(); it != files.end(); it++)
		{
			delete it->second;
			it->second = NULL;
		}
		files.clear();
	}
	return status;
}