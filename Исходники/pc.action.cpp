//extern Rect pc_area_buttons[6][6] ; // 0 - whole 1 - pic 2 - name 3 - stat strs 4,5 - later
//extern Rect item_string_rects[24][4]; // 0 - name 1 - drop  2 - id  3 - 
bool handle_action(EventRecord event,short mode)
//short mode; // ignore,
{
	short i;
	
	Point the_point;
	short choice = 4;
	
	bool to_return = false;

	the_point = event.where;
	GlobalToLocal(&the_point);	

	if (file_in_mem == false) 
		return false;
		
	for (i = 0; i < 6; i++)
		if ((PtInRect(the_point,&pc_area_buttons[i][0]) == true) &&
			(univ.party[i].main_status > 0)) {
			do_button_action(0,i);
			current_active_pc = i;
			display_party(6,1);
			draw_items(1);
			}
	for (i = 0; i < 5; i++)
		if ((PtInRect(the_point,&edit_rect[i][0]) == true) &&
			(univ.party[current_active_pc].main_status > 0)) {
			do_button_action(0,i + 10);
			if (save_blocked == false)
				if ((choice = FCD(904,0)) == 1)
					return to_return;
					else save_blocked = true;
			switch(i) {
				case 0:
					display_pc(current_active_pc,0,0);
					break;
				case 1:
			 		display_pc(current_active_pc,1,0);
					break;
				case 2: 
					pick_race_abil(&univ.party[current_active_pc],0,0);
					break;
				case 3: 
					spend_xp(current_active_pc,1,0);
					break;
				case 4: 
					edit_xp(&univ.party[current_active_pc]);
					
					break;
			}
		}
	for (i = 0; i < 24; i++)
		if ((PtInRect(the_point,&item_string_rects[i][1]) == true) && // drop item
			(univ.party[current_active_pc].items[i].variety > 0)) { // variety = 0 no item in slot/ non 0 item exists
				flash_rect(item_string_rects[i][1]);
				take_item(current_active_pc,i);
				draw_items(1);
				}
	for (i = 0; i < 24; i++)
		if ((PtInRect(the_point,&item_string_rects[i][2]) == true) && // identify item
			(univ.party[current_active_pc].items[i].variety > 0)) {
				flash_rect(item_string_rects[i][2]);
				univ.party[current_active_pc].items[i].ident = true;
				draw_items(1);
				}
	
	return to_return;
}