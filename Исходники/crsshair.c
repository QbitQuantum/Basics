static void create_bitmap(running_machine &machine, int player)
{
	int x, y;
	char filename[20];
	rgb_t color = crosshair_colors[player];

	/* if we have a bitmap and texture for this player, kill it */
	if (global.bitmap[player] == NULL)
		global.bitmap[player] = global_alloc(bitmap_argb32);
	machine.render().texture_free(global.texture[player]);

	emu_file crossfile(machine.options().crosshair_path(), OPEN_FLAG_READ);
	if (global.name[player][0] != 0)
	{
		/* look for user specified file */
		sprintf(filename, "%s.png", global.name[player]);
		render_load_png(*global.bitmap[player], crossfile, NULL, filename);
	}
	else
	{
		/* look for default cross?.png in crsshair\game dir */
		sprintf(filename, "cross%d.png", player + 1);
		render_load_png(*global.bitmap[player], crossfile, machine.system().name, filename);

		/* look for default cross?.png in crsshair dir */
		if (!global.bitmap[player]->valid())
			render_load_png(*global.bitmap[player], crossfile, NULL, filename);
	}

	/* if that didn't work, use the built-in one */
	if (!global.bitmap[player]->valid())
	{
		/* allocate a blank bitmap to start with */
		global.bitmap[player]->allocate(CROSSHAIR_RAW_SIZE, CROSSHAIR_RAW_SIZE);
		global.bitmap[player]->fill(MAKE_ARGB(0x00,0xff,0xff,0xff));

		/* extract the raw source data to it */
		for (y = 0; y < CROSSHAIR_RAW_SIZE / 2; y++)
		{
			/* assume it is mirrored vertically */
			UINT32 *dest0 = &global.bitmap[player]->pix32(y);
			UINT32 *dest1 = &global.bitmap[player]->pix32(CROSSHAIR_RAW_SIZE - 1 - y);

			/* extract to two rows simultaneously */
			for (x = 0; x < CROSSHAIR_RAW_SIZE; x++)
				if ((crosshair_raw_top[y * CROSSHAIR_RAW_ROWBYTES + x / 8] << (x % 8)) & 0x80)
					dest0[x] = dest1[x] = MAKE_ARGB(0xff,0x00,0x00,0x00) | color;
		}
	}

	/* create a texture to reference the bitmap */
	global.texture[player] = machine.render().texture_alloc(render_texture::hq_scale);
	global.texture[player]->set_bitmap(*global.bitmap[player], global.bitmap[player]->cliprect(), TEXFORMAT_ARGB32);
}