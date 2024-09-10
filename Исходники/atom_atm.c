static void image_fread_memory(device_image_interface &image, UINT16 addr, UINT32 count)
{
	void *ptr = image.device().machine().firstcpu->memory().space(AS_PROGRAM)->get_write_ptr(addr);

	image.fread( ptr, count);
}