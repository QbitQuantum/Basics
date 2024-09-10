void __stdcall initialise_automap_blobs()
{
	module_base = reinterpret_cast<unsigned>(GetModuleHandle(module_name));
	if(module_base == 0)
		automap_blobs_interrupt();
	
	unsigned * call_addresses[] =
	{
		&get_y_coordinate,
		&sub_6FACF710,
		&D2Common_10195,
		&D2Win_10132,
		&D2Lang_10005,
		&draw_text,
		&sub_6FACF780,
		&get_unit_state,
		&D2Common_10860,
		&automap_unit_type_check,
		&sub_6FAEDE00,
		&D2Common_10350,
		&sub_6FAB2D40,
		&draw_cross,
		&sub_6FACF3D0,
		&set_text_size,
		&get_x_coordinate
	};
	
	unsigned linking_offset = module_base - image_base;
	
	for(std::size_t i = 0; i < 17; i++)
	{
		unsigned & address = *call_addresses[i];
		address += linking_offset;
	}
	
	bool success = false;
	
	std::string const marker = "\x0f\x0b\x0f\x0b\x0f\x0b\x0f\x0b";
	
	char * data_pointer = reinterpret_cast<char *>(&automap_blobs);
	while(true)
	{
		std::string current_string(data_pointer, marker.size());
		if(current_string == marker)
		{
			success = true;
			break;
		}
		data_pointer++;
	}
	
	if(!success)
		automap_blobs_interrupt();
	
	data_pointer += marker.size();
	
	for(unsigned i = 0; i < 19; i++)
	{
		char * label_pointer = *reinterpret_cast<char **>(data_pointer + 1);
		unsigned * immediate_pointer = reinterpret_cast<unsigned *>(label_pointer - 4);
		DWORD old_protection;
		SIZE_T const patch_size = 4;
		if(!VirtualProtect(immediate_pointer, patch_size, PAGE_EXECUTE_READWRITE, &old_protection))
			automap_blobs_interrupt();
		unsigned & address = *immediate_pointer;
		address += linking_offset;
		DWORD unused;
		if(!VirtualProtect(immediate_pointer, patch_size, old_protection, &unused))
			automap_blobs_interrupt();
		data_pointer += 5;
	}
}