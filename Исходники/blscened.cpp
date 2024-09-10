Boolean handle_menu (short item, HMENU menu)
{
	short i;
	Boolean to_return = FALSE;
	short item_hit;
	Boolean need_redraw = FALSE;
	item_hit = item;

	switch (item) {
   	case -1: break;
		case 1: // open
			load_scenario();
			if (overall_mode == 60) {
				update_item_menu();
				set_up_main_screen();
				}
			break;
		case 2: // save
			modify_lists();
			save_scenario();
			break;
		case 3: // new scen
			build_scenario();
			if (overall_mode == 60)
				set_up_main_screen();
			break;

		case 5: // quit
			if (save_check(869) == FALSE)
				break;
			discard_graphics();
			PostQuitMessage(0);
			break;

			// Scenario Menu

		case 101:
			if (change_made == TRUE) {
				give_error("You need to save the changes made to your scenario before you can add a new town.",
					"",0);
				return to_return;
				}
			if (scenario.num_towns >= 200) {
				give_error("You have reached the limit of 200 towns you can have in one scenario.",
					"",0);
				return to_return;
				}
			if (new_town(scenario.num_towns) == TRUE)
				set_up_main_screen();
			break;
		case 103:
			edit_scen_details();
			break;
		case 104:
			edit_scen_intro();
			break;
		case 105:
			set_starting_loc();
			break;
		case 106: overall_mode = 47;
			set_string("Select party starting location.","");
			break;
		case 109:
            lpsi.fMask = SIF_POS;
            lpsi.nPos = 0;
            SetScrollInfo(right_sbar,SB_CTL,&lpsi,TRUE);
            //SetScrollPos(right_sbar,SB_CTL,0,TRUE);
            start_special_editing(0,0); break;
		case 110:
            lpsi.fMask = SIF_POS;
            lpsi.nPos = 0;
            SetScrollInfo(right_sbar,SB_CTL,&lpsi,TRUE);
			 //SetScrollPos(right_sbar,SB_CTL,0,TRUE);
             start_string_editing(0,0);
			break;
		case 111:
			if (change_made == TRUE) {
				give_error("You need to save the changes made to your scenario before you can add a new town.",
					"",0);
				return to_return;
				}
			i = pick_import_town(841,0);
			if (i >= 0) {
				import_town(i);
				change_made = TRUE;
				redraw_screen();
				}
			break;
		case 112:
			edit_save_rects();
			break;
		case 113:
			edit_horses();
			break;
		case 114:
			edit_boats();
			break;
		case 115:
			edit_add_town();
			break;
		case 116:
			edit_scenario_events();
			break;
		case 117:
			edit_item_placement();
			break;
		case 118:
			if (change_made == TRUE) {
				give_error("You need to save the changes made to your scenario before you can delete a town.",
					"",0);
				return to_return;
				}
			if (scenario.num_towns == 1) {
				give_error("You can't delete the last town in a scenario. All scenarios must have at least 1 town.",
					"",0);
				return to_return;
				}
			if (scenario.num_towns - 1 == cur_town) {
				give_error("You can't delete the last town in a scenario while you're working on it. Load a different town, and try this again.",
					"",0);
				return to_return;
				}
			if (scenario.num_towns - 1 == scenario.which_town_start) {
				give_error("You can't delete the last town in a scenario while it's the town the party starts the scenario in. Change the parties starting point and try this again.",
					"",0);
				return to_return;
				}
			if (fancy_choice_dialog(865,0) == 1)
				delete_last_town();
			break;
		case 119:
			if (fancy_choice_dialog(866,0) == 1) {
        last_file_printed = 0;
				start_data_dump();
				}
			break;
		case 120:
			if (change_made == TRUE) {
				give_error("You need to save the changes made to your scenario before you can print the file Scenario Text.",
					"",0);
				return to_return;
				}
			if (fancy_choice_dialog(871,0) == 1) {
        last_file_printed = 1;
				scen_text_dump();
			redraw_screen();
			}
			break;

		case 121:
			if (fancy_choice_dialog(867,0) == 1) {
        last_file_printed = 2;
				start_shopping_data_dump();
				}
		break;
		case 122:
			if (fancy_choice_dialog(868,0) == 1) {
        last_file_printed = 3;
				start_monst_data_dump();
				}
		break;
    case 123:
			if (fancy_choice_dialog(890,0) == 1) {
         last_file_printed = 4;
         start_spec_data_dump();
				}
    break;
		case 124:
			if (fancy_choice_dialog(878,0) == 1) {
      	 last_file_printed = 7;
				 object_scenario_data_dump();
			}
			break;


			// Town Menu
		case 201: edit_town_details(); break;
		case 202: edit_town_wand(); break;
		case 203: 							overall_mode = 9;
			mode_count = 2;
			set_cursor(5);
			set_string("Set town boundary","Select upper left corner");
			break;
		case 204: frill_up_terrain(); break;
		case 205: unfrill_terrain(); break;
		case 206: edit_town_strs(); break;
		case 208: if (fancy_choice_dialog(863,0) == 2) // add random
					break;
				place_items_in_town();
				 break;
		case 209: for (i = 0; i < 64; i++) // set not prop
					town.preset_items[i].property = 0;
				fancy_choice_dialog(861,0);
				draw_terrain();
				break;
		case 210: if (fancy_choice_dialog(862,0) == 2) // clear all items
					break;
				for (i = 0; i < 64; i++)
					town.preset_items[i].item_code = -1;
				draw_terrain();
				break;
		case 213:
            lpsi.fMask = SIF_POS;
            lpsi.nPos = 0;
            SetScrollInfo(right_sbar,SB_CTL,&lpsi,TRUE);
            //SetScrollPos(right_sbar,SB_CTL,0,TRUE);
             start_special_editing(2,0); break;
		case 214:
            lpsi.fMask = SIF_POS;
            lpsi.nPos = 0;
            SetScrollInfo(right_sbar,SB_CTL,&lpsi,TRUE);
            //SetScrollPos(right_sbar,SB_CTL,0,TRUE);
        start_string_editing(2,0); break;
		case 215: edit_advanced_town(); break;
		case 216: edit_town_events(); break;
		case 217: if (fancy_choice_dialog(872,0) == 2) // clear all monsters
					break;
				for (i = 0; i < 60; i++) {
						t_d.creatures[i].number = 0;
						t_d.creatures[i].start_loc.x = 0;
						t_d.creatures[i].start_loc.y = 0;
						t_d.creatures[i].spec_enc_code = 0;
						t_d.creatures[i].time_flag = 0;
                        t_d.creatures[i].spec1 = -1;
                        t_d.creatures[i].spec2 = -1;
						}
		break;
		case 218: if (fancy_choice_dialog(873,0) == 2) // clear all special encounters
					break;
					for (i = 0; i < 50; i++) {
							town.special_locs[i].x = 100;
							town.special_locs[i].y = 0;
							town.spec_id[i] = 255;
							}
		break;
		case 219: if (fancy_choice_dialog(874,0) == 2) // clear all fields
					break;
				for (i = 0; i < 50; i++)
						if ((town.preset_fields[i].field_type >= 0) && (town.preset_fields[i].field_type < 9)) {
						town.preset_fields[i].field_type = 0;
						town.preset_fields[i].field_loc.x = 0;
						town.preset_fields[i].field_loc.y = 0;
						}
		break;

		case 220: if (fancy_choice_dialog(876,0) == 2) // clear all stains
					break;
				for (i = 0; i < 50; i++)
						if ((town.preset_fields[i].field_type > 13) && (town.preset_fields[i].field_type < 22)) {
						town.preset_fields[i].field_type = 0;
						town.preset_fields[i].field_loc.x = 0;
						town.preset_fields[i].field_loc.y = 0;
						}
		break;

		case 221:    if (fancy_choice_dialog(877,0) == 1) { // make concise town report
		              last_file_printed = 5;
									start_town_data_dump();
									}
			break;

		case 222:
					start_dialogue_editing(0);
		break;


			// Outdoor Menu
		case 301: outdoor_details(); break;
		case 302: edit_out_wand(0); break;
		case 303: edit_out_wand(1); break;
		case 304: frill_up_terrain(); break;
		case 305: unfrill_terrain(); break;
		case 306: edit_out_strs(); break;
		case 307: if (fancy_choice_dialog(875,0) == 2) // clear all special encounters
					break;
					for (i = 0; i < 18; i++) {
							current_terrain.special_locs[i].x = 100;
							current_terrain.special_locs[i].y = 0;
							current_terrain.special_id[i] = 255;
							}

		case 311:
            lpsi.fMask = SIF_POS;
            lpsi.nPos = 0;
            SetScrollInfo(right_sbar,SB_CTL,&lpsi,TRUE);
            //SetScrollPos(right_sbar,SB_CTL,0,TRUE);
            start_special_editing(1,0); break;
		case 312:
            lpsi.fMask = SIF_POS;
            lpsi.nPos = 0;
            SetScrollInfo(right_sbar,SB_CTL,&lpsi,TRUE);
            //SetScrollPos(right_sbar,SB_CTL,0,TRUE);
            start_string_editing(1,0); break;
		break;

		case 313:
			if (fancy_choice_dialog(879,0) == 1) {
				 last_file_printed = 6;
				 start_outdoor_data_dump();
				 }
			break;

		case 401:
				 start_town_edit();
		break;
		case 402:
				 start_out_edit();
		break;
		case 403:
			short x, y;
			location spot_hit;

			if (editing_town == false) {

							if (change_made == TRUE) {
								if (save_check(859) == FALSE)
									break;
								}
							x = pick_out(cur_out);
							if (x >= 0) {
								spot_hit.x = x / 100;
								spot_hit.y = x % 100;
								load_outdoors(spot_hit,0);
								augment_terrain(spot_hit);
								start_out_edit();
								}

							}
			else {
							if (change_made == TRUE) {
								if (save_check(859) == FALSE)
									break;
								}
							x = pick_town_num(855,cur_town);
							if (x >= 0) {
								load_town(x);
								start_town_edit();
								}
							}
			break;
		case 404:
                    set_up_main_screen();
					start_terrain_editing();
		break;
		case 405:
                    set_up_main_screen();
					start_monster_editing(0);
		break;
		case 406:
					start_item_editing(0);
		break;
		case 407:
					set_up_main_screen();
		break;

		case 408: // switch view
				cur_viewing_mode = 1 - cur_viewing_mode;
				need_redraw = TRUE;
				draw_main_screen();
				draw_terrain();
		break;

		case 409: // load previous town/outdoor zone
					if (editing_town == true) {
								if (cur_town == 0)
								load_town(scenario.num_towns - 1);
								else load_town(cur_town - 1);
								start_town_edit();
						 }
			 else {
							if (cur_out.x > 0) {
							 x = cur_out.x - 1;
				 			 y = cur_out.y;
				 			 }
							if ((cur_out.x == 0) && (cur_out.y > 0)) {
				 			x = scenario.out_width - 1;
				 			y = cur_out.y - 1;
				 			}
							if ((cur_out.x == 0) && (cur_out.y == 0)) {
				 			x = scenario.out_width - 1;
				 			y = scenario.out_height - 1;
				 			}
								spot_hit.x = x;
								spot_hit.y = y;
								load_outdoors(spot_hit,0);
								augment_terrain(spot_hit);
								start_out_edit();
						}
		break;

		case 410: // load next town/outdoor zone
					if (editing_town == true) {
								if (cur_town + 1 == scenario.num_towns)
								load_town(0);
								else load_town(cur_town + 1);
								start_town_edit();
						 }
				 else {
				 			if ((cur_out.x < (scenario.out_width - 1)) && (cur_out.y <= (scenario.out_height - 1))) {
				 			x = cur_out.x + 1;
				 			y = cur_out.y;
				 			}
							if ((cur_out.x == (scenario.out_width - 1)) && (cur_out.y < (scenario.out_height - 1))) {
							x = 0;
				 			y = cur_out.y + 1;
							}
							if ((cur_out.x == (scenario.out_width - 1)) && (cur_out.y == (scenario.out_height - 1))) {
							x = 0;
							y = 0;
							}
								spot_hit.x = x;
								spot_hit.y = y;
								load_outdoors(spot_hit,0);
								augment_terrain(spot_hit);
								start_out_edit();
						 }
			break;

			case 411: //   MENUITEM "Terrain Animations Play", 411

            HMENU menu,big_menu;
            big_menu = GetMenu(mainPtr);
            menu = GetSubMenu(big_menu,4);

            if(play_anim == FALSE){
                play_anim = TRUE;
                CheckMenuItem(menu,411,MF_BYCOMMAND | MF_CHECKED);
                }
            else{
                play_anim = FALSE;
                CheckMenuItem(menu,411,MF_BYCOMMAND | MF_UNCHECKED);
                }
            break;

		case 412: // load outdoor zone above
							if (editing_town)
							break;
							if (cur_out.y > 0) {
							 x = cur_out.x;
				 			 y = cur_out.y - 1;
				 			 }
							else {
							 x = cur_out.x;
				 			y = scenario.out_height - 1;
				 			}
								spot_hit.x = x;
								spot_hit.y = y;
								load_outdoors(spot_hit,0);
								augment_terrain(spot_hit);
								start_out_edit();
		break;

		case 413: // load outdoor zone below
							if (editing_town)
							break;
							if (cur_out.y == scenario.out_height - 1) {
							 x = cur_out.x;
				 			 y = 0;
				 			 }
							else {
							 x = cur_out.x;
				 			 y = cur_out.y + 1;
				 			}
								spot_hit.x = x;
								spot_hit.y = y;
								load_outdoors(spot_hit,0);
								augment_terrain(spot_hit);
								start_out_edit();
		break;

		case 414: //   Repeat print of last file printed
         switch (last_file_printed){
            case 0:
				start_data_dump();
		    break;

            case 1:
				scen_text_dump();
            break;

            case 2:
				start_shopping_data_dump();
			break;

            case 3:
				start_monst_data_dump();
            break;

            case 4:
             start_spec_data_dump();
            break;

            case 5:
				start_town_data_dump();
            break;

            case 6:
				 start_outdoor_data_dump();
            break;

            case 7:
				 object_scenario_data_dump();
            break;
            }
		break;

				// Extra Help
		case 801: // help file
			WinHelp(mainPtr,"Scenario Editor.hlp",HELP_CONTENTS,0L);
			break;
		case 802: fancy_choice_dialog(986,0); break; // started
		case 803: fancy_choice_dialog(1000,0); break; // testing
		case 804: fancy_choice_dialog(1001,0); break; // distributing
		case 805:
		fancy_choice_dialog(1062,0);
		break;

		default:
			if ((overall_mode >= 60) || (editing_town == FALSE)) {
				give_error("You can only place items and individual monsters in town sections, not outdoors.","",0);
				break;
				}
			if ((item_hit >= 600) && (item_hit < 1000)) {
				item_hit -= 600;
				if (scen_item_list.scen_items[item_hit].variety == 0) {
					give_error("This item has its Variety set to No Item. You can only place items with a Variety set to an actual item type.","",0);
					return to_return;
					}
				overall_mode = 4;
				set_string("Place the item.","Select item location");
				mode_count = item_hit;
				}
//       skip the type 0 monster, it is non-existent
			if ((item_hit >= 1001) && (item_hit <= 1255)) { // 1,255?
				overall_mode = 28;
            item_hit -= 1000;
				set_string("Place the monster.","Select monster location");
				mode_count = item_hit;
				}
/*
			if ((item_hit >= 1256) && (item_hit <= 1455)) {
            item_hit -= 1256;
								mode_count = item_hit;
								load_town(item_hit);
								start_town_edit();
//				set_string("Loading the indicated town."," ");

				}
*/
			break;

		}
	if ((item >= 100) && (item < 200) && (item != 118) && (item != 119))
		change_made = TRUE;

	return to_return;
}