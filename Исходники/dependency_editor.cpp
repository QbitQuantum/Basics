void DependencyRemoveDialog::ok_pressed() {

	DirAccess *da = DirAccess::create(DirAccess::ACCESS_RESOURCES);
	for (Map<String, TreeItem *>::Element *E = files.front(); E; E = E->next()) {
		if (da->dir_exists(E->key())) {
			String path = OS::get_singleton()->get_resource_dir() + E->key().replace_first("res://", "/");
			OS::get_singleton()->move_path_to_trash(path);
			EditorFileSystem::get_singleton()->scan();
		} else {
			if (ResourceCache::has(E->key())) {
				Resource *res = ResourceCache::get(E->key());
				res->set_path(""); //clear reference to path
			}
			da->remove(E->key());
			EditorFileSystem::get_singleton()->update_file(E->key());
		}
	}
	memdelete(da);
}