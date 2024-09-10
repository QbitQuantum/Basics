void loadModules() {
	struct dirent *file;
	debug("Loading modules in %s",module_path);
	DIR* dir = opendir(module_path);
	if (!dir) die(6,"Failed to open module directory path %s",module_path);
	while (file = readdir(dir)) loadModule(file->d_name);
	closedir(dir);	
}