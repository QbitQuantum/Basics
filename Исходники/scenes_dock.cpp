void ScenesDock::_favorites_pressed() {

	TreeItem *sel = tree->get_selected();
	if (!sel)
		return ;
	String dir = sel->get_metadata(0);

	int idx = -1;
	Vector<String> favorites = EditorSettings::get_singleton()->get_favorite_dirs();
	for(int i=0;i<favorites.size();i++) {

		if (favorites[i]==dir) {
			idx=i;
			break;
		}
	}

	if (button_favorite->is_pressed() && idx==-1) {
		favorites.push_back(dir);
		EditorSettings::get_singleton()->set_favorite_dirs(favorites);
		_update_tree();
	} else if (!button_favorite->is_pressed() && idx!=-1) {
		favorites.remove(idx);
		EditorSettings::get_singleton()->set_favorite_dirs(favorites);
		_update_tree();
	}

}