static int plus4_crt_load( device_image_interface &image )
{
	UINT8 *mem = image.device().machine().root_device().memregion("maincpu")->base();
	int size = image.length(), test;
	const char *filetype;
	int address = 0;

	/* magic lowrom at offset 7: $43 $42 $4d */
	/* if at offset 6 stands 1 it will immediatly jumped to offset 0 (0x8000) */
	static const unsigned char magic[] = {0x43, 0x42, 0x4d};
	unsigned char buffer[sizeof (magic)];

	image.fseek(7, SEEK_SET);
	image.fread( buffer, sizeof (magic));
	image.fseek(0, SEEK_SET);

	/* Check if our cart has the magic string, and set its loading address */
	if (!memcmp(buffer, magic, sizeof (magic)))
		address = 0x20000;

	/* Give a loading address to non .bin / non .rom carts as well */
	filetype = image.filetype();

	/* We would support .hi and .lo files, but currently I'm not sure where to load them.
       We simply load them at 0x20000 at this stage, even if it's probably wrong!
       It could also well be that they both need to be loaded at the same time, but this
       is now impossible since I reduced to 1 the number of cart slots.
       More investigations are in order if any .hi, .lo dump would surface!              */
	if (!mame_stricmp(filetype, "hi"))
		address = 0x20000;	/* FIX ME! */

	else if (!mame_stricmp(filetype, "lo"))
		address = 0x20000;	/* FIX ME! */

	/* As a last try, give a reasonable loading address also to .bin/.rom without the magic string */
	else if (!address)
	{
		logerror("Cart %s does not contain the magic string: it may be loaded at the wrong memory address!\n", image.filename());
		address = 0x20000;
	}

	logerror("Loading cart %s at %.5x size:%.4x\n", image.filename(), address, size);

	/* Finally load the cart */
	test = image.fread( mem + address, size);

	if (test != size)
		return IMAGE_INIT_FAIL;

	return IMAGE_INIT_PASS;
}