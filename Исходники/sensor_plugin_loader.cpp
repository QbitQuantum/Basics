bool sensor_plugin_loader::load_module(const string &path, vector<void*> &sensors, void* &handle)
{
	void *_handle = dlopen(path.c_str(), RTLD_NOW);

	if (!_handle) {
		ERR("Failed to dlopen(%s), dlerror : %s", path.c_str(), dlerror());
		return false;
	}

	dlerror();

	create_t create_module = (create_t) dlsym(_handle, "create");

	if (!create_module) {
		ERR("Failed to find symbols in %s", path.c_str());
		dlclose(_handle);
		return false;
	}

	sensor_module *module = create_module();

	if (!module) {
		ERR("Failed to create module, path is %s\n", path.c_str());
		dlclose(_handle);
		return false;
	}

	sensors.clear();
	sensors.swap(module->sensors);

	delete module;
	handle = _handle;

	return true;
}