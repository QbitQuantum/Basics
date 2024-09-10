// initialize all popup details (graphics, etc)
void multi_pinfo_popup_init(net_player *np)
{
	int idx;
	
	// no errors to start with
	Multi_pinfo_popup_error = 0;

	// shouldn't be done
	Multi_pinfo_popup_done = 0;

	// store the background as it currently is
	Multi_pinfo_screen_save = gr_save_screen();
	if(Multi_pinfo_screen_save == -1){
		Multi_pinfo_popup_error = 1;
		return;
	}

	// create the interface window
	Multi_pinfo_window.create(0,0,gr_screen.max_w_unscaled,gr_screen.max_h_unscaled,0);
	Multi_pinfo_window.set_mask_bmap(Multi_pinfo_bitmap_mask[gr_screen.res]);

	// load the background bitmap
	Multi_pinfo_bitmap = bm_load(Multi_pinfo_bitmap_name[gr_screen.res]);
	if(Multi_pinfo_bitmap < 0){
		Multi_pinfo_popup_error = 1;
		return;	
	}

	// backup hardware textures setting and bash to max
	Multi_pinfo_hardware_texture_backup = Detail.hardware_textures;
	Detail.hardware_textures = MAX_DETAIL_LEVEL;

	// zero bitmap info
	Mp_pilot.bitmap = -1;
	strcpy_s(Mp_pilot.filename, "");
	Mp_squad.bitmap = -1;
	strcpy_s(Mp_squad.filename, "");

	// set the player status
	multi_pinfo_reset_player(np);	
	
	// create the interface buttons
	for(idx=0;idx<MULTI_PINFO_NUM_BUTTONS;idx++){
		// create the object
		Multi_pinfo_buttons[gr_screen.res][idx].button.create(&Multi_pinfo_window, "", Multi_pinfo_buttons[gr_screen.res][idx].x, Multi_pinfo_buttons[gr_screen.res][idx].y, 1, 1, 0, 1);

		// set the sound to play when highlighted
		Multi_pinfo_buttons[gr_screen.res][idx].button.set_highlight_action(common_play_highlight_sound);

		// set the ani for the button
		Multi_pinfo_buttons[gr_screen.res][idx].button.set_bmaps(Multi_pinfo_buttons[gr_screen.res][idx].filename);

		// set the hotspot
		Multi_pinfo_buttons[gr_screen.res][idx].button.link_hotspot(Multi_pinfo_buttons[gr_screen.res][idx].hotspot);
	}			

	// add xstrs
	for(idx=0; idx<MULTI_PINFO_NUM_TEXT; idx++){
		Multi_pinfo_window.add_XSTR(&Multi_pinfo_text[gr_screen.res][idx]);
	}

	// initialize strings	
	Multi_pinfo_stats_labels[0] = vm_strdup(XSTR("Rank", 1007));
	Multi_pinfo_stats_labels[1] = vm_strdup(XSTR("Missions Flown", 1008));
	Multi_pinfo_stats_labels[2] = vm_strdup(XSTR("Flight Time", 1009));
	Multi_pinfo_stats_labels[3] = vm_strdup(XSTR("Last Flown",1010));
	Multi_pinfo_stats_labels[4] = vm_strdup(XSTR("Total Kills", 115));
	Multi_pinfo_stats_labels[5] = vm_strdup(XSTR("Primary Shots Fired", 1012));
	Multi_pinfo_stats_labels[6] = vm_strdup(XSTR("Primary Hit %", 1013));
	Multi_pinfo_stats_labels[7] = vm_strdup(XSTR("Secondary Shots Fired",	1014));
	Multi_pinfo_stats_labels[8] = vm_strdup(XSTR("Secondary Hit %", 1015));				
}