int game(int where, int where_num)
{
	MOUSEMSG m;
	int temp_x, temp_y, i, j, flag = 0, num = 480/where;
	int step = 0;

	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN && m.x < 480)
		{
			if (m.x == num || m.y == num)
			{
				continue;
			}
			mciSendString("open audio/change.mp3 alias change", NULL, 0, NULL);
			mciSendString("play change", NULL, 0, NULL);
			step += 1;
			temp_x = m.x/num;
			temp_y = m.y/num;
			if (map_check[temp_y][temp_x] == 0)
			{
				setfillstyle(RED);
				floodfill(m.x, m.y , GREEN);
				map_check[temp_y][temp_x] = 1;
			}
			else
			{
				setfillstyle(BLACK);
				floodfill(m.x, m.y, GREEN);
				map_check[temp_y][temp_x] = 0;
			}
			if (temp_x - 1 >= 0)
			{
				if (map_check[temp_y][temp_x-1])
				{
					setfillstyle(BLACK);
					floodfill(m.x - num, m.y, GREEN);
					map_check[temp_y][temp_x-1] = 0;
				}
				else
				{
					setfillstyle(RED);
					floodfill(m.x - num, m.y, GREEN);
					map_check[temp_y][temp_x-1] = 1;
				}
			}
			if (temp_y - 1 >= 0)
			{
				if (map_check[temp_y-1][temp_x])
				{
					setfillstyle(BLACK);
					floodfill(m.x, m.y - num, GREEN);
					map_check[temp_y-1][temp_x] = 0;
				}
				else
				{
					setfillstyle(RED);
					floodfill(m.x, m.y - num, GREEN);
					map_check[temp_y-1][temp_x] = 1;
				}
			}
			if (temp_x + 1 < where)
			{
				if (map_check[temp_y][temp_x+1])
				{
					setfillstyle(BLACK);
					floodfill(m.x + num, m.y, GREEN);
					map_check[temp_y][temp_x+1] = 0;
				}
				else
				{
					setfillstyle(RED);
					floodfill(m.x + num, m.y , GREEN);
					map_check[temp_y][temp_x+1] = 1;
				}
			}
			if (temp_y + 1 < where)
			{
				if (map_check[temp_y+1][temp_x])
				{
					setfillstyle(BLACK);
					floodfill(m.x, m.y + num, GREEN);
					map_check[temp_y+1][temp_x] = 0;
				}
				else
				{
					setfillstyle(RED);
					floodfill(m.x, m.y + num, GREEN);
					map_check[temp_y+1][temp_x] = 1;
				}
			}
			Sleep(200);
			mciSendString("stop change", NULL, 0, NULL);
			mciSendString("close change", NULL, 0, NULL);
		}
		for (i = 0; i < where && !flag; i++)
		{
			for (j = 0; j < where && !flag; j++)
			{
				if (map_check[i][j] == 0)
				{
					flag = 1;
				}
			}
		}
		game_info(flag, step, where_num);
		if (flag == 0)
		{
			break;
		}
		flag = 0;
	}
	return 0;
}