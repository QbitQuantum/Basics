int window_new_identity_run_command(gui_t* gui, int c)
{
    ogmp_curses_t* ocui = gui->topui;

    int max = 5;

    switch (c)
    {
    case KEY_DC:
    {
        editline_remove_char(newid_edit[cursor_newid]);

        delch();

        break;
    }
    case '\b':
    {
        if (editline_move_pos(newid_edit[cursor_newid], -1) >= 0)
            editline_remove_char(newid_edit[cursor_newid]);
        else
            beep();

        break;
    }
    case '\n':
    case '\r':
    case KEY_ENTER:
    case KEY_DOWN:
    {
        cursor_newid++;
        cursor_newid %= max;

        break;
    }
    case KEY_UP:
    {
        cursor_newid += max-1;
        cursor_newid %= max;

        break;
    }
    case KEY_RIGHT:
    {
        if (editline_move_pos(newid_edit[cursor_newid], 1) < 0)
            beep();

        break;
    }
    case KEY_LEFT:
    {
        if (editline_move_pos(newid_edit[cursor_newid], -1) < 0)
            beep();

        break;
    }
    case 1:  /* Ctrl-A */
    {
        int sec = 0;

        if(newid_regsec[0])
            sec = strtol(newid_regsec, NULL, 10);

        if(sec <= 0)
            break;

        if(newid_fullname[0] && newid_registary[0] && newid_regname[0])
        {
            if(!ocui->edit_profile)
                user_add_profile(ocui->user, newid_fullname, strlen(newid_fullname),
                                 newid_bookloc, newid_registary, newid_regname, sec);
            else
                user_set_profile(ocui->user, ocui->edit_profile, newid_fullname, strlen(newid_fullname),
                                 newid_bookloc, newid_registary, newid_regname, sec);

            gui_hide_window(gui);
        }

        break;
    }
    case 3:  /* Ctrl-C */
    {
        gui_hide_window(gui);

        break;
    }
    case 4:  /* Ctrl-D */
    {
        editline_clear(newid_edit[cursor_newid]);

        break;
    }
    default:
    {
        if(editline_append(newid_edit[cursor_newid], (char*)&c, 1) == 0)
        {
            beep();

            return -1;
        }
    }
    }

    gui_update(gui);

    return 0;
}