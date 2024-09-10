static void draw_sprites(running_machine &machine, bitmap_ind16 &bitmap,const rectangle &cliprect)
{
	crshrace_state *state = machine.driver_data<crshrace_state>();
	UINT16 *buffered_spriteram = machine.generic.buffered_spriteram.u16;
	UINT16 *buffered_spriteram_2 = machine.generic.buffered_spriteram2.u16;
	int offs;

	offs = 0;
	while (offs < 0x0400 && (buffered_spriteram[offs] & 0x4000) == 0)
	{
		int attr_start;
		int map_start;
		int ox, oy, x, y, xsize, ysize, zoomx, zoomy, flipx, flipy, color;
		/* table hand made by looking at the ship explosion in aerofgt attract mode */
		/* it's almost a logarithmic scale but not exactly */
		static const int zoomtable[16] = { 0,7,14,20,25,30,34,38,42,46,49,52,54,57,59,61 };

		attr_start = 4 * (buffered_spriteram[offs++] & 0x03ff);

		ox = buffered_spriteram[attr_start + 1] & 0x01ff;
		xsize = (buffered_spriteram[attr_start + 1] & 0x0e00) >> 9;
		zoomx = (buffered_spriteram[attr_start + 1] & 0xf000) >> 12;
		oy = buffered_spriteram[attr_start + 0] & 0x01ff;
		ysize = (buffered_spriteram[attr_start + 0] & 0x0e00) >> 9;
		zoomy = (buffered_spriteram[attr_start + 0] & 0xf000) >> 12;
		flipx = buffered_spriteram[attr_start + 2] & 0x4000;
		flipy = buffered_spriteram[attr_start + 2] & 0x8000;
		color = (buffered_spriteram[attr_start + 2] & 0x1f00) >> 8;
		map_start = buffered_spriteram[attr_start + 3] & 0x7fff;

		zoomx = 16 - zoomtable[zoomx] / 8;
		zoomy = 16 - zoomtable[zoomy] / 8;

		if (buffered_spriteram[attr_start + 2] & 0x20ff) color = machine.rand();

		for (y = 0; y <= ysize; y++)
		{
			int sx,sy;

			if (flipy) sy = ((oy + zoomy * (ysize - y) + 16) & 0x1ff) - 16;
			else sy = ((oy + zoomy * y + 16) & 0x1ff) - 16;

			for (x = 0; x <= xsize; x++)
			{
				int code;

				if (flipx) sx = ((ox + zoomx * (xsize - x) + 16) & 0x1ff) - 16;
				else sx = ((ox + zoomx * x + 16) & 0x1ff) - 16;

				code = buffered_spriteram_2[map_start & 0x7fff];
				map_start++;

				if (state->m_flipscreen)
					drawgfxzoom_transpen(bitmap,cliprect,machine.gfx[2],
							code,
							color,
							!flipx,!flipy,
							304-sx,208-sy,
							0x1000 * zoomx,0x1000 * zoomy,15);
				else
					drawgfxzoom_transpen(bitmap,cliprect,machine.gfx[2],
							code,
							color,
							flipx,flipy,
							sx,sy,
							0x1000 * zoomx,0x1000 * zoomy,15);
			}
		}
	}
}