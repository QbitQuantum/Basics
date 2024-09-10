void
gui_key_flush (int paste)
{
    int i, key, last_key_used, insert_ok, undo_done;
    static char key_str[64] = { '\0' };
    static int length_key_str = 0;
    char key_temp[2], *key_utf, *input_old, *ptr_char, *next_char, *ptr_error;
    char utf_partial_char[16];
    struct t_gui_buffer *old_buffer;

    /* if paste pending or bracketed paste detected, just return */
    if (gui_key_paste_pending || gui_key_paste_bracketed)
        return;

    /* if buffer is empty, just return */
    if (gui_key_buffer_size == 0)
        return;

    /*
     * if there's no paste pending, then we use buffer and do actions
     * according to keys
     */
    gui_key_last_activity_time = time (NULL);
    last_key_used = -1;
    undo_done = 0;
    old_buffer = NULL;
    for (i = 0; i < gui_key_buffer_size; i++)
    {
        key = gui_key_buffer[i];
        insert_ok = 1;
        utf_partial_char[0] = '\0';

        if (gui_mouse_event_pending || (key < 32) || (key == 127))
        {
            if (gui_mouse_event_pending)
            {
                insert_ok = 0;
                key_str[0] = (char)key;
                key_str[1] = '\0';
                length_key_str = 1;
            }
            else if (key < 32)
            {
                insert_ok = 0;
                key_str[0] = '\x01';
                key_str[1] = (char)key + '@';
                key_str[2] = '\0';
                length_key_str = 2;
            }
            else if (key == 127)
            {
                key_str[0] = '\x01';
                key_str[1] = '?';
                key_str[2] = '\0';
                length_key_str = 2;
            }
        }
        else
        {
            if (local_utf8)
            {
                key_str[length_key_str] = (char)key;
                key_str[length_key_str + 1] = '\0';
                length_key_str++;

                /*
                 * replace invalid chars by "?", but NOT last char of
                 * string, if it is incomplete UTF-8 char (another char
                 * will be added to the string on next iteration)
                 */
                ptr_char = key_str;
                while (ptr_char && ptr_char[0])
                {
                    (void) utf8_is_valid (ptr_char, &ptr_error);
                    if (!ptr_error)
                        break;
                    next_char = utf8_next_char (ptr_error);
                    if (next_char && next_char[0])
                    {
                        ptr_char = ptr_error;
                        while (ptr_char < next_char)
                        {
                            ptr_char[0] = '?';
                            ptr_char++;
                        }
                    }
                    else
                    {
                        strcpy (utf_partial_char, ptr_char);
                        ptr_char[0] = '\0';
                        break;
                    }
                    ptr_char = next_char;
                }
            }
            else
            {
                /* convert input to UTF-8 */
                key_temp[0] = (char)key;
                key_temp[1] = '\0';
                key_utf = string_iconv_to_internal (NULL, key_temp);
                strcat (key_str, key_utf);
            }
        }

        if (key_str[0])
        {
            hook_signal_send ("key_pressed",
                              WEECHAT_HOOK_SIGNAL_STRING, key_str);

            if (gui_current_window->buffer->text_search != GUI_TEXT_SEARCH_DISABLED)
                input_old = (gui_current_window->buffer->input_buffer) ?
                    strdup (gui_current_window->buffer->input_buffer) : strdup ("");
            else
                input_old = NULL;
            old_buffer = gui_current_window->buffer;

            if ((gui_key_pressed (key_str) != 0) && (insert_ok)
                && (!gui_cursor_mode))
            {
                if (!paste || !undo_done)
                    gui_buffer_undo_snap (gui_current_window->buffer);
                gui_input_insert_string (gui_current_window->buffer,
                                         key_str, -1);
                gui_input_text_changed_modifier_and_signal (gui_current_window->buffer,
                                                            (!paste || !undo_done) ? 1 : 0,
                                                            1); /* stop completion */
                undo_done = 1;
            }

            /* incremental text search in buffer */
            if ((old_buffer == gui_current_window->buffer)
                && (gui_current_window->buffer->text_search != GUI_TEXT_SEARCH_DISABLED)
                && ((input_old == NULL)
                    || (gui_current_window->buffer->input_buffer == NULL)
                    || (strcmp (input_old, gui_current_window->buffer->input_buffer) != 0)))
            {
                /*
                 * if following conditions are all true, then do not search
                 * again (search will not find any result and can take some time
                 * on a buffer with many lines):
                 * - old search was not successful
                 * - searching a string (not a regex)
                 * - current input is longer than old input
                 * - beginning of current input is exactly equal to old input.
                 */
                if (!gui_current_window->buffer->text_search_found
                    && !gui_current_window->buffer->text_search_regex
                    && (input_old != NULL)
                    && (input_old[0])
                    && (gui_current_window->buffer->input_buffer != NULL)
                    && (gui_current_window->buffer->input_buffer[0])
                    && (strlen (gui_current_window->buffer->input_buffer) > strlen (input_old))
                    && (strncmp (gui_current_window->buffer->input_buffer, input_old,
                                 strlen (input_old)) == 0))
                {
                    /*
                     * do not search text in buffer, just alert about text not
                     * found
                     */
                    if (CONFIG_BOOLEAN(config_look_search_text_not_found_alert))
                        printf ("\a");
                }
                else
                {
                    gui_window_search_restart (gui_current_window);
                }
            }

            if (input_old)
                free (input_old);
        }

        /* prepare incomplete UTF-8 char for next iteration */
        if (utf_partial_char[0])
            strcpy (key_str, utf_partial_char);
        else
            key_str[0] = '\0';
        length_key_str = strlen (key_str);

        /* set last key used in buffer if combo buffer is empty */
        if (gui_key_grab || gui_mouse_event_pending || !gui_key_combo_buffer[0])
            last_key_used = i;
    }

    if (last_key_used == gui_key_buffer_size - 1)
        gui_key_buffer_reset ();
    else if (last_key_used >= 0)
        gui_key_buffer_remove (0, last_key_used + 1);

    if (!gui_key_grab && !gui_mouse_event_pending)
        gui_key_combo_buffer[0] = '\0';
}