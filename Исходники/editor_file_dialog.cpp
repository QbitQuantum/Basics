void EditorFileDialog::_save_to_recent() {

	String dir = get_current_dir();
	Vector<String> recent = EditorSettings::get_singleton()->get_recent_dirs();

	const int max=20;
	int count=0;
	bool res=dir.begins_with("res://");

	for(int i=0;i<recent.size();i++) {
		bool cres=recent[i].begins_with("res://");
		if (recent[i]==dir || (res==cres && count>max)) {
			recent.remove(i);
			i--;
		} else {
			count++;
		}
	}

	recent.insert(0,dir);

	EditorSettings::get_singleton()->set_recent_dirs(recent);


}