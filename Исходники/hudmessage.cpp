void hud_scrollback_do_frame(float frametime)
{
    int i, k, x, y;
    int font_height = gr_get_font_height();

    k = Ui_window.process();
    switch (k) {
    case KEY_RIGHT:
    case KEY_TAB:
        if (Scrollback_mode == SCROLLBACK_MODE_OBJECTIVES) {
            Scrollback_mode = SCROLLBACK_MODE_MSGS_LOG;
            Scroll_max = hud_query_scrollback_size();
            hud_scroll_reset();

        } else if (Scrollback_mode == SCROLLBACK_MODE_MSGS_LOG) {
            Scrollback_mode = SCROLLBACK_MODE_EVENT_LOG;
            Scroll_max = Num_log_lines * gr_get_font_height();
            hud_scroll_reset();

        } else {
            Scrollback_mode = SCROLLBACK_MODE_OBJECTIVES;
            Scroll_max = Num_obj_lines * gr_get_font_height();
            Scroll_offset = 0;
        }

        break;

    case KEY_LEFT:
    case KEY_SHIFTED | KEY_TAB:
        if (Scrollback_mode == SCROLLBACK_MODE_OBJECTIVES) {
            Scrollback_mode = SCROLLBACK_MODE_EVENT_LOG;
            Scroll_max = Num_log_lines * gr_get_font_height();
            hud_scroll_reset();

        } else if (Scrollback_mode == SCROLLBACK_MODE_MSGS_LOG) {
            Scrollback_mode = SCROLLBACK_MODE_OBJECTIVES;
            Scroll_max = Num_obj_lines * gr_get_font_height();
            Scroll_offset = 0;

        } else {
            Scrollback_mode = SCROLLBACK_MODE_MSGS_LOG;
            Scroll_max = hud_query_scrollback_size();
            hud_scroll_reset();
        }

        break;

    case KEY_PAGEUP:
        hud_page_scroll_list(1);
        break;

    case KEY_PAGEDOWN:
        hud_page_scroll_list(0);
        break;

    case KEY_ENTER:
    case KEY_CTRLED | KEY_ENTER:
    case KEY_ESC:
        hud_scrollback_exit();
        break;

    case KEY_F1:  // show help overlay
        break;

    case KEY_F2:  // goto options screen
        gameseq_post_event(GS_EVENT_OPTIONS_MENU);
        break;
    }	// end switch

    for (i=0; i<NUM_BUTTONS; i++) {
        if (Buttons[gr_screen.res][i].button.pressed()) {
            hud_scrollback_button_pressed(i);
        }
    }

    GR_MAYBE_CLEAR_RES(Background_bitmap);
    if (Background_bitmap >= 0) {
        gr_set_bitmap(Background_bitmap);
        gr_bitmap(0, 0, GR_RESIZE_MENU);
    }

    /*
    if ((Scrollback_mode == SCROLLBACK_MODE_OBJECTIVES) && (Status_bitmap >= 0)) {
    	gr_set_bitmap(Status_bitmap);
    	gr_bitmap(Hud_mission_log_status_coords[gr_screen.res][0], Hud_mission_log_status_coords[gr_screen.res][1], GR_RESIZE_MENU);
    }
    */

    // draw the objectives key at the bottom of the ingame objectives screen
    if (Scrollback_mode == SCROLLBACK_MODE_OBJECTIVES) {
        ML_render_objectives_key();
    }

    Ui_window.draw();

    if (Scrollback_mode == SCROLLBACK_MODE_EVENT_LOG) {
        Buttons[gr_screen.res][SHOW_EVENTS_BUTTON].button.draw_forced(2);
        mission_log_scrollback(Scroll_offset, Hud_mission_log_list_coords[gr_screen.res][0], Hud_mission_log_list_coords[gr_screen.res][1], Hud_mission_log_list_coords[gr_screen.res][2], Hud_mission_log_list_coords[gr_screen.res][3]);

    } else if (Scrollback_mode == SCROLLBACK_MODE_OBJECTIVES) {
        Buttons[gr_screen.res][SHOW_OBJS_BUTTON].button.draw_forced(2);
        ML_objectives_do_frame(Scroll_offset);

    } else {
        line_node *node_ptr;

        Buttons[gr_screen.res][SHOW_MSGS_BUTTON].button.draw_forced(2);
//		y = ((LIST_H / font_height) - 1) * font_height;
        y = 0;
        if ( !EMPTY(&Msg_scrollback_used_list) && HUD_msg_inited ) {
            node_ptr = GET_FIRST(&Msg_scrollback_used_list);
            i = 0;
            while ( node_ptr != END_OF_LIST(&Msg_scrollback_used_list) ) {
                if ((node_ptr->source == HUD_SOURCE_HIDDEN) || (i++ < Scroll_offset)) {
                    node_ptr = GET_NEXT(node_ptr);

                } else {
                    int team = HUD_source_get_team(node_ptr->source);

                    if (team >= 0)
                    {
                        gr_set_color_fast(iff_get_color_by_team(team, Player_ship->team, 0));
                    }
                    else
                    {
                        switch (node_ptr->source)
                        {
                        case HUD_SOURCE_TRAINING:
                            gr_set_color_fast(&Color_bright_blue);
                            break;

                        case HUD_SOURCE_TERRAN_CMD:
                            gr_set_color_fast(&Color_bright_white);
                            break;

                        case HUD_SOURCE_IMPORTANT:
                        case HUD_SOURCE_FAILED:
                        case HUD_SOURCE_SATISFIED:
                            gr_set_color_fast(&Color_bright_white);
                            break;

                        default:
                            gr_set_color_fast(&Color_text_normal);
                            break;
                        }
                    }

                    if (node_ptr->time)
                        gr_print_timestamp(Hud_mission_log_list_coords[gr_screen.res][0], Hud_mission_log_list_coords[gr_screen.res][1] + y, node_ptr->time, GR_RESIZE_MENU);

                    x = Hud_mission_log_list2_coords[gr_screen.res][0] + node_ptr->x;
                    gr_printf_menu(x, Hud_mission_log_list_coords[gr_screen.res][1] + y, "%s", node_ptr->text);
                    if (node_ptr->underline_width)
                        gr_line(x, Hud_mission_log_list_coords[gr_screen.res][1] + y + font_height - 1, x + node_ptr->underline_width, Hud_mission_log_list_coords[gr_screen.res][1] + y + font_height - 1, GR_RESIZE_MENU);

                    if ((node_ptr->source == HUD_SOURCE_FAILED) || (node_ptr->source == HUD_SOURCE_SATISFIED)) {
                        // draw goal icon
                        if (node_ptr->source == HUD_SOURCE_FAILED)
                            gr_set_color_fast(&Color_bright_red);
                        else
                            gr_set_color_fast(&Color_bright_green);

                        i = Hud_mission_log_list_coords[gr_screen.res][1] + y + font_height / 2 - 1;
                        gr_circle(Hud_mission_log_list2_coords[gr_screen.res][0] - 6, i, 5, GR_RESIZE_MENU);

                        gr_set_color_fast(&Color_bright);
                        gr_line(Hud_mission_log_list2_coords[gr_screen.res][0] - 10, i, Hud_mission_log_list2_coords[gr_screen.res][0] - 8, i, GR_RESIZE_MENU);
                        gr_line(Hud_mission_log_list2_coords[gr_screen.res][0] - 6, i - 4, Hud_mission_log_list2_coords[gr_screen.res][0] - 6, i - 2, GR_RESIZE_MENU);
                        gr_line(Hud_mission_log_list2_coords[gr_screen.res][0] - 4, i, Hud_mission_log_list2_coords[gr_screen.res][0] - 2, i, GR_RESIZE_MENU);
                        gr_line(Hud_mission_log_list2_coords[gr_screen.res][0] - 6, i + 2, Hud_mission_log_list2_coords[gr_screen.res][0] - 6, i + 4, GR_RESIZE_MENU);
                    }

                    y += font_height + node_ptr->y;
                    node_ptr = GET_NEXT(node_ptr);
                    if (y + font_height > Hud_mission_log_list_coords[gr_screen.res][3])
                        break;
                }
            }
        }
    }

    gr_set_color_fast(&Color_text_heading);
    gr_print_timestamp(Hud_mission_log_time_coords[gr_screen.res][0], Hud_mission_log_time_coords[gr_screen.res][1] - font_height, Missiontime, GR_RESIZE_MENU);
    gr_string(Hud_mission_log_time2_coords[gr_screen.res][0], Hud_mission_log_time_coords[gr_screen.res][1] - font_height, XSTR( "Current time", 289), GR_RESIZE_MENU);
    gr_flip();
}