/* this is the actual draw function for a single field
 */
static void draw_single_field (uint8_t in_x, uint8_t in_y, game_field_t in_f)
{
	pixel tmp;
	uint8_t b;
	switch (in_f)
	{
		case b1:
			b = 1;
		break;

		case rb:
		case b2:
			b = 2;
		break;

		case b3:
		case bl:
		case bs:
			b = 3;
		break;

		default: /* this includes freespace */
			b = 0;
		break;

	}
	tmp.x = in_x;
	tmp.y = in_y;
	setpixel (tmp, b);
}