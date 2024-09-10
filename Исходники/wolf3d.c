static float	ray_caster_h(t_data *d, float ray_a)
{
	float	int_hy;
	float	int_hx;
	float	xa;
	float	ya;

	if (ray_a <= WEST)
		int_hy = (d->p.y / CUBE) * (CUBE) - 1;
	else
		int_hy = (d->p.y / CUBE) * (CUBE) + CUBE;
	int_hx = d->p.x + (d->p.y - int_hy) / TAN(ray_a);
	ya = (ray_a <= WEST) ? -CUBE : CUBE;
	xa = -ya / TAN(ray_a);
	while ((int_hx >= 0 && int_hx < CUBE * MAP_H)
			&& (int_hy >= 0 && int_hy < CUBE * MAP_H))
	{
		if (d->map[(int)(int_hy / CUBE)][(int)(int_hx / CUBE)] != 0)
			return (sqrt(pow(d->p.x - int_hx, 2) + pow(d->p.y - int_hy, 2)));
		int_hx += xa;
		int_hy += ya;
	}
	return (MAX_DS);
}