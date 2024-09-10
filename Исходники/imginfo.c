void ui_menu_image_info::image_info_astring(running_machine &machine, astring &string)
{
	string.printf("%s\n\n", machine.system().description);

#if 0
	if (mess_ram_size > 0)
	{
		char buf2[RAM_STRING_BUFLEN];
		string.catprintf("RAM: %s\n\n", ram_string(buf2, mess_ram_size));
	}
#endif

	image_interface_iterator iter(machine.root_device());
	for (device_image_interface *image = iter.first(); image != NULL; image = iter.next())
	{
		const char *name = image->filename();
		if (name != NULL)
		{
			const char *base_filename;
			const char *info;
			char *base_filename_noextension;

			base_filename = image->basename();
			base_filename_noextension = strip_extension(base_filename);

			// display device type and filename
			string.catprintf("%s: %s\n", image->device().name(), base_filename);

			// display long filename, if present and doesn't correspond to name
			info = image->longname();
			if (info && (!base_filename_noextension || core_stricmp(info, base_filename_noextension)))
				string.catprintf("%s\n", info);

			// display manufacturer, if available
			info = image->manufacturer();
			if (info != NULL)
			{
				string.catprintf("%s", info);
				info = stripspace(image->year());
				if (info && *info)
					string.catprintf(", %s", info);
				string.catprintf("\n");
			}

			// display supported information, if available
			switch(image->supported()) {
				case SOFTWARE_SUPPORTED_NO : string.catprintf("Not supported\n"); break;
				case SOFTWARE_SUPPORTED_PARTIAL : string.catprintf("Partially supported\n"); break;
				default : break;
			}

			if (base_filename_noextension != NULL)
				free(base_filename_noextension);
		}
		else
		{
			string.catprintf("%s: ---\n", image->device().name());
		}
	}
}