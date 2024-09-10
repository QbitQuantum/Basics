int		check_line(t_point *res, t_point *pos, t_point *dir, int max)
{
	int	index;
	int tmp_x;
	int tmp_y;

	tmp_x = pos->x;
	tmp_y = pos->y;
	while (tmp_x != max && tmp_y != max)
	{
		if (IS_IN_MAP(PLAYER_X) && IS_IN_MAP(PLAYER_Y))
		{
			index = NORMALIZE(PLAYER_X, PLAYER_Y);
			if (IS_ENEMY(g_shm.data[index]))
			{
				res->x = tmp_x;
				res->y = tmp_y;
				return (1);
			}
		}
		tmp_x += dir->x;
		tmp_y += dir->y;
	}
	return (0);
}