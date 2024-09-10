image_init_result n64_mess_state::disk_load(device_image_interface &image)
{
	image.fseek(0, SEEK_SET);
	image.fread(memregion("disk")->base(), image.length());
	machine().device<n64_periphs>("rcp")->disk_present = true;
	return image_init_result::PASS;
}