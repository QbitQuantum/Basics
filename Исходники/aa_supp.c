static t_color		get_color_sample(t_data *data,
					 t_bunny_position *p)
{
  t_bunny_position	pos;
  t_3d_pos		color;
  t_color		actcolor;

  actcolor.full = BLACK;
  color.x = 0;
  color.y = 0;
  color.z = 0;
  pos.y = p->y * AA_SAMPLE;
  while (pos.y < p->y * AA_SAMPLE + AA_SAMPLE)
    {
      pos.x = p->x * AA_SAMPLE;
      while (pos.x < p->x * AA_SAMPLE + AA_SAMPLE)
	{
	  color.x += getpixel(data->pix, &pos).argb[0];
	  color.y += getpixel(data->pix, &pos).argb[1];
	  color.z += getpixel(data->pix, &pos).argb[2];
	  pos.x += 1;
	}
      pos.y += 1;
    }
  actcolor.argb[0] = color.x / (double)(AA_SAMPLE * AA_SAMPLE);
  actcolor.argb[1] = color.y / (double)(AA_SAMPLE * AA_SAMPLE);
  actcolor.argb[2] = color.z / (double)(AA_SAMPLE * AA_SAMPLE);
  return (actcolor);
}