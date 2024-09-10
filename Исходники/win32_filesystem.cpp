	PathString make_absolute_path(const char* path)
	{
		PathString buffer;
		ExpandEnvironmentStringsA(path, &buffer[0], MAX_PATH_SIZE);

		PathString full_path;
		GetFullPathNameA(&buffer[0], MAX_PATH_SIZE, &full_path[0], NULL);

		// since StackString is being used as a c-style array here,
		// we have to force it to recompute its c-string size.
		full_path.recompute_size();
		return full_path;
	}