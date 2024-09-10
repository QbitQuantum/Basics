void ExportTemplateManager::_uninstall_template_confirm() {

	DirAccess *d = DirAccess::create(DirAccess::ACCESS_FILESYSTEM);
	Error err = d->change_dir(EditorSettings::get_singleton()->get_templates_dir());

	ERR_FAIL_COND(err != OK);

	err = d->change_dir(to_remove);

	ERR_FAIL_COND(err != OK);

	Vector<String> files;

	d->list_dir_begin();

	bool isdir;
	String c = d->get_next(&isdir);
	while (c != String()) {
		if (!isdir) {
			files.push_back(c);
		}
		c = d->get_next(&isdir);
	}

	d->list_dir_end();

	for (int i = 0; i < files.size(); i++) {
		d->remove(files[i]);
	}

	d->change_dir("..");
	d->remove(to_remove);

	_update_template_list();
}