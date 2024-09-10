void accel_table_t::add(WORD cmd, std::string key) {
	size_t pos = 0;
	bool ctrl = false, alt = false, shift = false;
	while(true) {
		if(key.substr(pos, 5) == "Ctrl+") {
			ctrl = true;
			pos += 5;
		} else if(key.substr(pos, 4) == "Alt+") {
			alt = true;
			pos += 4;
		} else if(key.substr(pos, 6) == "Shift+") {
			shift = true;
			pos += 6;
		} else if(pos >= key.size()) return;
		else break;
	}
	WORD keycode;
	key = key.substr(pos);
	if(key.length() == 0) return;
	else if(key.length() == 1) {
		SHORT virtkey = VkKeyScanA(key[0]);
		keycode = LOBYTE(virtkey);
	} else if(key[0] == 'F') {
		std::istringstream parse;
		parse.str(key.substr(1));
		int fkey = -1;
		parse >> fkey;
		// We allow for 24 F-keys because that's how many VK_Fx constants there are
		if(fkey <= 0 || fkey > 24)
			return;
		keycode = VK_F1 + fkey - 1;
	} else if(key == "Backsp") keycode = VK_BACK;