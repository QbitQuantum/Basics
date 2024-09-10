void end_battle(void*d)
{
	{char window_title[255];sprintf_s(window_title,255,"SAWD [SPOILS OF WAR] - %s", 
	GAME_BUILD_NUMBER); SetConsoleTitle(window_title);}

	clibwindow* black_panel = cl->open_window_noframe(0,0,79,49,0,0);
	// the enemy that was defeated is passed to this function
	obj* e = (obj*)d;

	int box[] = {16, 5, 48, 30};
	int x = box[0] + 2;
	int y = box[1] + 2;

	clibwindow* upg_wnd = cl->open_window(box[0], box[1], box[2], box[3]);

	unsigned long xp_gained		= e->experience;
	unsigned long nxt_xp		= xp_to_level_up();
	unsigned long gold_gained	= e->gold;

	cl->outcharsf(x, 32, "$%8d", player->gold);
	draw_player_stats_end_battle(x, y);
	// update the experience
	bool next_upg = false; unsigned int counter = 0;
	while(!next_upg)
	{
		cl->outcharsf(x, y, "Battle Experience: %8d / %8d", player->experience, nxt_xp);
		player->experience++;
		if (player->experience >= nxt_xp)
		{
			level_up();
			nxt_xp = xp_to_level_up();
			draw_player_stats_end_battle(x, y); // update stats
		}

		counter++;
		if (counter >= xp_gained)
		{
			next_upg = true;
		}

		unsigned long start_time = timeGetTime();
		while((timeGetTime() - start_time) < 60);
	}

	// update the gold
	next_upg = false;
	counter = 0;
	while(!next_upg)
	{
		cl->outcharsf(x, 32, "$%8d", player->gold);
		player->gold++;
		counter++;
		if (counter >= gold_gained)
		{
			next_upg = true;
		}

		unsigned long start_time = timeGetTime();
		while((timeGetTime() - start_time) < 60);
	}

	// show items gained if any
	if (e->items.size()>0)
	{
		display_items_gained(e);

		for (unsigned int i = 0; i < e->items.size(); i++)
		{
			player->items.push_back(get_master_item(e->items.at(i)->name));
		}
	}

	cl->show_message_centered(3,"","Another Victory!","");
	cl->close_window(upg_wnd);
	cl->close_window(black_panel);
}