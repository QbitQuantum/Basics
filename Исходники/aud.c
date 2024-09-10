//implemetation of functions
int start_finding(int start_x, int start_y)
{
	int inter = 0;
	int token = 0;
	int cur_x = start_x, cur_y = start_y;
	int dir = SOUTH;
	int ppath = -1;
	int npop = 0;	//how many points should be poped
	struct POINT *cur_p = NULL;
	struct POINT *tmp_p = NULL;
	int ret = 0;

	#ifdef DEBUG
	inter = Robot_GetIntersections();
	#else
	inter = get_intersection();
	#endif

	cur_p = mark_point(cur_x, cur_y, inter);
	dir = get_direction(cur_p);

	#ifdef DEBUG
	printf("start point: ");
	print_point(cur_p);
	printf("\n");
	#endif

	while(token < TOKEN_COUNT)
	{
		#ifdef DEBUG
		//inter = Robot_GetIntersections();
		//print_intersection(inter);
		#endif

		if(points[cur_x][cur_y].detected == 0)
			cur_p = mark_point(cur_x, cur_y, inter);
		else
			cur_p = &points[cur_x][cur_y];
		push(cur_p);
		//print_stack();

		if(dir = get_direction(cur_p))
		{
			//update current point
			switch(dir)
			{
				case EAST:
					cur_x += 1;
					break;
				case SOUTH:
					cur_y -= 1;
					break;
				case WEST:
					cur_x -= 1;
					break;
				case NORTH:
					cur_y += 1;
					break;
			}

			#ifdef DEBUG
			print_direction(cur_p, dir);
			ret = aud_move(cur_p, dir);
			#else
			//move one step
			display_clear(0);
			display_goto_xy(0, 0);
			display_int(cur_p->x, 2);
			display_goto_xy(3, 0);
			display_int(cur_p->y, 2);
			display_goto_xy(7, 0);
			display_int(cur_x, 2);
			display_goto_xy(10, 0);
			display_int(cur_y, 2);
			display_goto_xy(0, 1);
			display_int(g_dir, 3);
			display_goto_xy(5, 1);
			display_int(dir, 3);
			display_goto_xy(0, 2);
			display_int(cur_p->inter&0xF0, 3);
			display_update();

			ret = move(cur_x, cur_y);
			#endif

			#ifdef DEBUG
			inter = Robot_GetIntersections();
			#else
			inter = get_intersection();
			#endif

			cur_p = mark_point(cur_x, cur_y, inter);

			#ifdef DEBUG
			print_point(cur_p);
			#endif

			if(ret == ROBOT_SUCCESS)
			{
				#ifndef DEBUG
				#endif
			}
			else if(ret == ROBOT_TOKENFOUND)
			{
				tmp_p = &points[cur_x][cur_y];
				if(tmp_p->has_token == 0)
				{
					tmp_p->has_token = 1;
					token++;
					#ifdef DEBUG
					printf("[%d. token]\n", token);
					#endif
				}
				else
				{
					#ifdef DEBUG
					printf("[not a new token]\n");
					#endif
				}

				if(token == TOKEN_COUNT)
				{
					//all token were found, go back to start point
					#ifdef DEBUG
					printf("going back to start point......\n");
					#endif
					push(cur_p);
					ppath = find_shortest_path(cur_p->x, cur_p->y, START_X, START_Y);
					if(ppath)
					{
						//going back to last open point
						ppath--;

						while(ppath >= 0)
						{
							tmp_p = shortest_path[ppath];
							dir = calc_direction(cur_p->x, cur_p->y, tmp_p->x, tmp_p->y);
							#ifdef DEBUG
							print_point(tmp_p);
							printf("\n");
							ROBOT_MOVE(tmp_p->x, tmp_p->y);
							#else
							display_clear(0);
							display_goto_xy(0, 0);
							display_int(cur_p->x, 2);
							display_goto_xy(3, 0);
							display_int(cur_p->y, 2);
							display_goto_xy(7, 0);
							display_int(tmp_p->x, 2);
							display_goto_xy(10, 0);
							display_int(tmp_p->y, 2);
							display_goto_xy(0, 1);
							display_int(g_dir, 3);
							display_goto_xy(5, 1);
							display_int(dir, 3);
							display_goto_xy(0, 2);
							display_int(cur_p->inter&0xF0, 3);
							display_update();

							move(tmp_p->x, tmp_p->y);
							#endif
							cur_p = tmp_p;
							ppath--;
						}

						//delete the path in stack
						pop(npop + 1);
						cur_p = tmp_p;
						cur_x = cur_p->x;
						cur_y = cur_p->y;
					}
					#ifdef DEBUG
					printf("task finished!\n");
					#else
					beep();
					#endif

					break;
				}
			}
			else
			{
				#ifdef DEBUG
				printf("move failed!\n");
				#endif
			}
		}
		else
		{
			//there is no ways forward, go back to nearest open point
			tmp_p = get_last_open_point();
			npop = stack_pointer - get_stack_index(tmp_p->x, tmp_p->y);
			#ifdef DEBUG
			printf("going back to (%d, %d)\n", tmp_p->x, tmp_p->y);
			#endif

			if(tmp_p)
			{
				if((tmp_p->x == START_X) && (tmp_p->y == START_Y) && !IS_OPEN_POINT(points[tmp_p->x][tmp_p->y]))
				{
					#ifdef DEBUG
					return 0;
					#else
					stop_robot();
					beep();
					return 0;
					#endif
				}
				ppath = find_shortest_path(cur_p->x, cur_p->y, tmp_p->x, tmp_p->y);

				if(ppath)
				{
					//going back to last open point
					ppath--;

					while(ppath >= 0)
					{
						tmp_p = shortest_path[ppath];
						dir = calc_direction(cur_p->x, cur_p->y, tmp_p->x, tmp_p->y);
						#ifdef DEBUG
						ROBOT_MOVE(tmp_p->x, tmp_p->y);
						#else
						display_clear(0);
						display_goto_xy(0, 0);
						display_int(cur_p->x, 2);
						display_goto_xy(3, 0);
						display_int(cur_p->y, 2);
						display_goto_xy(7, 0);
						display_int(tmp_p->x, 2);
						display_goto_xy(10, 0);
						display_int(tmp_p->y, 2);
						display_goto_xy(0, 1);
						display_int(g_dir, 3);
						display_goto_xy(5, 1);
						display_int(dir, 3);
						display_goto_xy(0, 2);
						display_int(cur_p->inter&0xF0, 3);
						display_update();

						move(tmp_p->x, tmp_p->y);
						#endif
						cur_p = tmp_p;
						ppath--;
					}

					//delete the path in stack
					pop(npop + 1);
					cur_p = tmp_p;
					cur_x = cur_p->x;
					cur_y = cur_p->y;
				}
				else
				{
					//was already at every point and back to start point
					//task should be ended
					//that means, not enough token can be found
					#ifdef DEBUG
					printf("task ended without enough token were found.\n");
					#endif
					break;
				}
			}
		}
		#ifdef DEBUG
		printf("\n");
		#endif
	}

	return 0;
}