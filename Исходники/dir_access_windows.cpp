bool DirAccessWindows::list_dir_begin() {

	_cisdir = false;
	_cishidden = false;

	list_dir_end();
	p->h = FindFirstFileExW((current_dir + "\\*").c_str(), FindExInfoStandard, &p->fu, FindExSearchNameMatch, NULL, 0);

	return (p->h == INVALID_HANDLE_VALUE);
}