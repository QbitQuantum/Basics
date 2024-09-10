void EditorFileSystem::_delete_internal_files(String p_file) {
	if (FileAccess::exists(p_file + ".import")) {
		List<String> paths;
		ResourceFormatImporter::get_singleton()->get_internal_resource_path_list(p_file, &paths);
		DirAccess *da = DirAccess::create(DirAccess::ACCESS_RESOURCES);
		for (List<String>::Element *E = paths.front(); E; E = E->next()) {
			da->remove(E->get());
		}
		da->remove(p_file + ".import");
		memdelete(da);
	}
}