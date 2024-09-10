static void f1gpb_draw_sprites( running_machine &machine, bitmap_ind16 &bitmap,const rectangle &cliprect )
{
	f1gp_state *state = machine.driver_data<f1gp_state>();
	UINT16 *spriteram = state->m_spriteram;
	int attr_start, start_offset = state->m_spriteram_size / 2 - 4;

	// find the "end of list" to draw the sprites in reverse order
	for (attr_start = 4; attr_start < state->m_spriteram_size / 2; attr_start += 4)
	{
		if (spriteram[attr_start + 3 - 4] == 0xffff) /* end of list marker */
		{
			start_offset = attr_start - 4;
			break;
		}
	}

	for (attr_start = start_offset;attr_start >= 4;attr_start -= 4)
	{
		int code, gfx;
		int x, y, flipx, flipy, color, pri;

		x = (spriteram[attr_start + 2] & 0x03ff) - 48;
		y = (256 - (spriteram[attr_start + 3 - 4] & 0x03ff)) - 15;
		flipx = spriteram[attr_start + 1] & 0x0800;
		flipy = spriteram[attr_start + 1] & 0x8000;
		color = spriteram[attr_start + 1] & 0x000f;
		code = spriteram[attr_start + 0] & 0x3fff;
		pri = 0; //?

		if((spriteram[attr_start + 1] & 0x00f0) && (spriteram[attr_start + 1] & 0x00f0) != 0xc0)
		{
			printf("attr %X\n",spriteram[attr_start + 1] & 0x00f0);
			code = machine.rand();
		}

/*
        if (spriteram[attr_start + 1] & ~0x88cf)
            printf("1 = %X\n", spriteram[attr_start + 1] & ~0x88cf);
*/
		if(code >= 0x2000)
		{
			gfx = 1;
			code -= 0x2000;
		}
		else
		{
			gfx = 0;
		}

		pdrawgfx_transpen(bitmap,cliprect,machine.gfx[1 + gfx],
			code,
			color,
			flipx,flipy,
			x,y,
			machine.priority_bitmap,
			pri ? 0 : 0x2,15);

		// wrap around x
		pdrawgfx_transpen(bitmap,cliprect,machine.gfx[1 + gfx],
			code,
			color,
			flipx,flipy,
			x - 512,y,
			machine.priority_bitmap,
			pri ? 0 : 0x2,15);
	}
}