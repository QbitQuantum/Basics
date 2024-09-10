int pcjr_state::load_cart(device_image_interface &image, generic_slot_device *slot)
{
	UINT32 size = slot->common_get_size("rom");
	bool imagic_hack = false;

	if (image.software_entry() == nullptr)
	{
		int header_size = 0;

		// Check for supported header sizes
		switch (size & 0x3ff)
		{
			case 0x80:
				header_size = 0x80;
				break;
			case 0x200:
				header_size = 0x200;
				break;
			default:
				image.seterror(IMAGE_ERROR_UNSUPPORTED, "Invalid header size" );
				return IMAGE_INIT_FAIL;
		}
		if (size - header_size == 0xa000)
		{
			// alloc 64K for the imagic carts, so to handle the necessary mirroring
			size += 0x6000;
			imagic_hack = true;
		}

		size -= header_size;
		image.fseek(header_size, SEEK_SET);
	}

	slot->rom_alloc(size, GENERIC_ROM8_WIDTH, ENDIANNESS_LITTLE);
	slot->common_load_rom(slot->get_rom_base(), size, "rom");

	if (imagic_hack)
	{
		// in this case the image consists of 2x8K chunks
		// the first chunk is unique, the second is repeated 4 times up to 0xa000 size

		// mirroring
		UINT8 *ROM = slot->get_rom_base();
		memcpy(ROM + 0xe000, ROM + 0x2000, 0x2000);
		memcpy(ROM + 0xc000, ROM + 0x2000, 0x2000);
		memcpy(ROM + 0xa000, ROM + 0x2000, 0x2000);
		memcpy(ROM + 0x8000, ROM + 0x2000, 0x2000);
		memcpy(ROM + 0x6000, ROM, 0x2000);
		memcpy(ROM + 0x4000, ROM, 0x2000);
		memcpy(ROM + 0x2000, ROM, 0x2000);
	}
	return IMAGE_INIT_PASS;
}