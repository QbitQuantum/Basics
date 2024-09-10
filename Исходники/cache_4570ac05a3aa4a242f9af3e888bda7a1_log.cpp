bool log::alloc_console_private()
{
	char image_path[MAX_STRING_SIZE] = {0};
	bool is_ok = true;
	PLOADED_IMAGE loaded_image_ptr = NULL;

	GetModuleFileNameA(NULL, image_path, sizeof(image_path));
	loaded_image_ptr = ImageLoad(image_path, NULL);

	switch(loaded_image_ptr->FileHeader->OptionalHeader.Subsystem){
	   case IMAGE_SUBSYSTEM_UNKNOWN:
			is_ok = false;
		   break;
	   case IMAGE_SUBSYSTEM_NATIVE:
	   case IMAGE_SUBSYSTEM_WINDOWS_GUI:
	   case IMAGE_SUBSYSTEM_OS2_CUI:
	   case IMAGE_SUBSYSTEM_NATIVE_WINDOWS:
	   case IMAGE_SUBSYSTEM_WINDOWS_CE_GUI:
		   if(AllocConsole() == FALSE) is_ok = false;
		   break;
	   case IMAGE_SUBSYSTEM_WINDOWS_CUI:
	   case IMAGE_SUBSYSTEM_POSIX_CUI:
		   break;
	}

	ImageUnload(loaded_image_ptr);
	std_output_handler_ = GetStdHandle(STD_OUTPUT_HANDLE);
	__matrix_setlocale(LC_ALL, __TEXT("chs"));
	return is_ok;
}