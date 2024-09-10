void *uwsgi_python_autoreloader_thread(void *foobar) {

	PyObject *new_thread = uwsgi_python_setup_thread("uWSGIAutoReloader");
	if (!new_thread) return NULL;

	PyObject *modules = PyImport_GetModuleDict();

	if (uwsgi.mywid == 1) {
		uwsgi_log("Python auto-reloader enabled\n");
	}

	PyObject *times_dict = PyDict_New();
	char *filename;
	for(;;) {
		UWSGI_RELEASE_GIL;
		sleep(up.auto_reload);
		UWSGI_GET_GIL;
		// do not start monitoring til the first app is loaded (required for lazy mode)
		if (uwsgi_apps_cnt == 0) continue;
#ifdef UWSGI_PYTHON_OLD
                int pos = 0;
#else
                Py_ssize_t pos = 0;
#endif
		PyObject *mod_name, *mod;
                while (PyDict_Next(modules, &pos, &mod_name, &mod)) {
			int found = 0;
			struct uwsgi_string_list *usl = up.auto_reload_ignore;
			while(usl) {
				if (!strcmp(usl->value, PyString_AsString(mod_name))) {
					found = 1;
					break;
				}
				usl = usl->next;
			}
			if (found) continue;
			if (!PyObject_HasAttrString(mod, "__file__")) continue;
			PyObject *mod_file = PyObject_GetAttrString(mod, "__file__");
			if (!mod_file) continue;
#ifdef PYTHREE
			PyObject *zero = PyUnicode_AsUTF8String(mod_file);
			char *mod_filename = PyString_AsString(zero);
#else
			char *mod_filename = PyString_AsString(mod_file);
#endif
			if (!mod_filename) {
#ifdef PYTHREE
				Py_DECREF(zero);
#endif
				continue;
			}
			char *ext = strrchr(mod_filename, '.');
			if (ext && (!strcmp(ext+1, "pyc") || !strcmp(ext+1, "pyd") || !strcmp(ext+1, "pyo"))) {
				filename = uwsgi_concat2n(mod_filename, strlen(mod_filename)-1, "", 0);
			}
			else {
				filename = uwsgi_concat2(mod_filename, "");
			}
			if (uwsgi_check_python_mtime(times_dict, filename)) {
				UWSGI_RELEASE_GIL;
				return NULL;
			}
			free(filename);
#ifdef PYTHREE
			Py_DECREF(zero);
#endif
		}
	}

	return NULL;
}