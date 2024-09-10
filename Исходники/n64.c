int n64_mess_state::quickload(device_image_interface &image, const char *file_type, int quickload_size)
{
	image.fseek(0, SEEK_SET);
	image.fread(memregion("disk")->base(), quickload_size);
	machine().device<n64_periphs>("rcp")->disk_present = true;
	return IMAGE_INIT_PASS;
}