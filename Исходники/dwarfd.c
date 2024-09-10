static void drawCrt( running_machine &machine, bitmap_rgb32 &bitmap,const rectangle &cliprect )
{
	dwarfd_state *state = machine.driver_data<dwarfd_state>();
	int x, y;
	for (y = 0; y < maxy; y++)
	{
		int count = y * 256;
		int bank2 = 4;

		if (y < TOPLINE || y > BOTTOMLINE)
		{
			bank2 = 0;
		}
		for (x = 0; x < maxx; x++)
		{
			int tile = 0;

			int b = 0; //end marker
			while (b == 0)
			{
				if (count < 0x8000)
					tile = state->m_videobuf[count++];
				else
						return;

				if (tile & 0x80)
				{
					if ((tile & 0xfc) == 0xf0)
					{
						switch (tile & 3)
						{
							case 0:
							case 1: break;

							case 2:
							case 3: return;
						}
					}
					if ((tile & 0xc0) == 0x80)
					{
						state->m_bank = (tile >> 2) & 3;
					}
					if ((tile & 0xc0) == 0xc0)
					{
						b = 1;
						tile = machine.rand() & 0x7f;//(tile >> 2) & 0xf;
					}
				}
				else
					b = 1;
			}
			drawgfx_transpen(bitmap, cliprect, machine.gfx[0],
				tile + (state->m_bank + bank2) * 128,
				0,
				0, 0,
				x*8,y*8,0);
		}