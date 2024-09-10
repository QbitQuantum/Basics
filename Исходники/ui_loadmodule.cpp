void LoadModuleView::on_show() {
	char md5_signature[16];
	uint8_t c;
	
	memcpy(md5_signature, (const void *)(0x10087FF0), 16);
	for (c=0; c<16; c++) {
		if (md5_signature[c] != _hash[c]) break;
	}
	//text_info.set(to_string_hex(*((unsigned int*)0x10087FF0), 8));
	
	if (c == 16) {
		text_info.set("Module already loaded :)");
		_mod_loaded = true;
	} else {
		text_info.set("Loading module");
		loadmodule();
	}
}