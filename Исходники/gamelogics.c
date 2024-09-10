/**
* can_move(void)
*
* @brief Determine if player is able to move
* @param void
* @return void
*/
sbool can_move(void)
{
	uint32 d;
	sbool ismap = FALSE;

	if(player(myindex())->moving)
		return FALSE;

	if(tempdata()->castedspell){
		if(gettickcount() > player(myindex())->attacktimer + 1)
			tempdata()->castedspell = FALSE;
		else
			return FALSE;
	}

	d = player(myindex())->dir;

	switch(tempdata()->dir){
	case DIR_NONE: return FALSE;
	case DIR_UP:
		player(myindex())->dir = DIR_UP;

		if(player(myindex())->y <= 0){
			if(map()->up) ismap = TRUE;
			return FALSE;
		}
		break;
	case DIR_DOWN:
		player(myindex())->dir = DIR_DOWN;

		if(player(myindex())->y >= MAX_MAPY - 1){
			if(map()->down) ismap = TRUE;
			return FALSE;
		}
		break;
	case DIR_LEFT:
		player(myindex())->dir = DIR_LEFT;

		if(player(myindex())->x <= 0){
			if(map()->left) ismap = TRUE;
			return FALSE;
		}
		break;

	case DIR_RIGHT:
		player(myindex())->dir = DIR_RIGHT;

		if(player(myindex())->x >= MAX_MAPX - 1){
			if(map()->right) ismap = TRUE;
			return FALSE;
		}
		break;
	}

	if(ismap){
		//map_editor_leave_map();
		request_new_map();
		tempdata()->gettingmap = TRUE;
		tempdata()->canmovenow = FALSE;
		return FALSE;
	}

	if(check_direction(player(myindex())->dir)){
		if(d != player(myindex())->dir)
			send_player_dir();

		return FALSE;
	}

	return TRUE;
}