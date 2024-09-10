char *
weechat_aspell_modifier_cb (const void *pointer, void *data,
                            const char *modifier,
                            const char *modifier_data, const char *string)
{
    long unsigned int value;
    struct t_gui_buffer *buffer;
    struct t_aspell_speller_buffer *ptr_speller_buffer;
    char *result, *ptr_string, *ptr_string_orig, *pos_space;
    char *ptr_end, *ptr_end_valid, save_end;
    char *word_for_suggestions, *old_suggestions, *suggestions;
    char *word_and_suggestions;
    const char *color_normal, *color_error, *ptr_suggestions;
    int code_point, char_size;
    int length, index_result, length_word, word_ok;
    int length_color_normal, length_color_error, rc;
    int input_pos, current_pos, word_start_pos, word_end_pos, word_end_pos_valid;

    /* make C compiler happy */
    (void) pointer;
    (void) data;
    (void) modifier;

    if (!aspell_enabled)
        return NULL;

    if (!string)
        return NULL;

    rc = sscanf (modifier_data, "%lx", &value);
    if ((rc == EOF) || (rc == 0))
        return NULL;

    buffer = (struct t_gui_buffer *)value;

    /* check text during search only if option is enabled */
    if (weechat_buffer_get_integer (buffer, "text_search")
        && !weechat_config_boolean (weechat_aspell_config_check_during_search))
        return NULL;

    /* get structure with speller info for buffer */
    ptr_speller_buffer = weechat_hashtable_get (weechat_aspell_speller_buffer,
                                                buffer);
    if (!ptr_speller_buffer)
    {
        ptr_speller_buffer = weechat_aspell_speller_buffer_new (buffer);
        if (!ptr_speller_buffer)
            return NULL;
    }
    if (!ptr_speller_buffer->spellers)
        return NULL;

    /*
     * for performance: return last string built if input string is the
     * same (and cursor position is the same, if suggestions are enabled)
     */
    input_pos = weechat_buffer_get_integer (buffer, "input_pos");
    if (ptr_speller_buffer->modifier_string
        && (strcmp (string, ptr_speller_buffer->modifier_string) == 0)
        && ((weechat_config_integer (weechat_aspell_config_check_suggestions) < 0)
            || (input_pos == ptr_speller_buffer->input_pos)))
    {
        return (ptr_speller_buffer->modifier_result) ?
            strdup (ptr_speller_buffer->modifier_result) : NULL;
    }

    /* free last modifier string and result */
    if (ptr_speller_buffer->modifier_string)
    {
        free (ptr_speller_buffer->modifier_string);
        ptr_speller_buffer->modifier_string = NULL;
    }
    if (ptr_speller_buffer->modifier_result)
    {
        free (ptr_speller_buffer->modifier_result);
        ptr_speller_buffer->modifier_result = NULL;
    }

    word_for_suggestions = NULL;

    /* save last modifier string received */
    ptr_speller_buffer->modifier_string = strdup (string);
    ptr_speller_buffer->input_pos = input_pos;

    color_normal = weechat_color ("bar_fg");
    length_color_normal = strlen (color_normal);
    color_error = weechat_color (weechat_config_string (weechat_aspell_config_color_misspelled));
    length_color_error = strlen (color_error);

    length = strlen (string);
    result = malloc (length + (length * length_color_error) + 1);

    if (result)
    {
        result[0] = '\0';

        ptr_string = ptr_speller_buffer->modifier_string;
        index_result = 0;

        /* check if string is a command */
        if (!weechat_string_input_for_buffer (ptr_string))
        {
            char_size = weechat_utf8_char_size (ptr_string);
            ptr_string += char_size;
            pos_space = ptr_string;
            while (pos_space && pos_space[0] && (pos_space[0] != ' '))
            {
                pos_space = (char *)weechat_utf8_next_char (pos_space);
            }
            if (!pos_space || !pos_space[0])
            {
                free (result);
                return NULL;
            }

            pos_space[0] = '\0';

            /* exit if command is not authorized for spell checking */
            if (!weechat_aspell_command_authorized (ptr_string))
            {
                free (result);
                return NULL;
            }
            memcpy (result + index_result,
                    ptr_speller_buffer->modifier_string,
                    char_size);
            index_result += char_size;
            strcpy (result + index_result, ptr_string);
            index_result += strlen (ptr_string);

            pos_space[0] = ' ';
            ptr_string = pos_space;
        }

        current_pos = 0;
        while (ptr_string[0])
        {
            ptr_string_orig = NULL;

            /* find start of word: it must start with an alphanumeric char */
            code_point = weechat_utf8_char_int (ptr_string);
            while ((!iswalnum (code_point)) || iswspace (code_point))
            {
                if (!ptr_string_orig && !iswspace (code_point))
                    ptr_string_orig = ptr_string;
                char_size = weechat_utf8_char_size (ptr_string);
                memcpy (result + index_result, ptr_string, char_size);
                index_result += char_size;
                ptr_string += char_size;
                current_pos++;
                if (!ptr_string[0])
                    break;
                code_point = weechat_utf8_char_int (ptr_string);
            }
            if (!ptr_string[0])
                break;
            if (!ptr_string_orig)
                ptr_string_orig = ptr_string;

            word_start_pos = current_pos;
            word_end_pos = current_pos;
            word_end_pos_valid = current_pos;

            /* find end of word: ' and - allowed in word, but not at the end */
            ptr_end_valid = ptr_string;
            ptr_end = (char *)weechat_utf8_next_char (ptr_string);
            code_point = weechat_utf8_char_int (ptr_end);
            while (iswalnum (code_point) || (code_point == '\'')
                   || (code_point == '-'))
            {
                word_end_pos++;
                if (iswalnum (code_point))
                {
                    /* pointer to last alphanumeric char in the word */
                    ptr_end_valid = ptr_end;
                    word_end_pos_valid = word_end_pos;
                }
                ptr_end = (char *)weechat_utf8_next_char (ptr_end);
                if (!ptr_end[0])
                    break;
                code_point = weechat_utf8_char_int (ptr_end);
            }
            ptr_end = (char *)weechat_utf8_next_char (ptr_end_valid);
            word_end_pos = word_end_pos_valid;
            word_ok = 0;
            if (weechat_aspell_string_is_url (ptr_string)
                || weechat_aspell_string_is_nick (buffer, ptr_string_orig))
            {
                /*
                 * word is an URL or a nick, then it is OK: search for next
                 * space (will be end of word)
                 */
                word_ok = 1;
                if (ptr_end[0])
                {
                    code_point = weechat_utf8_char_int (ptr_end);
                    while (!iswspace (code_point))
                    {
                        ptr_end = (char *)weechat_utf8_next_char (ptr_end);
                        if (!ptr_end[0])
                            break;
                        code_point = weechat_utf8_char_int (ptr_end);
                    }
                }
            }
            save_end = ptr_end[0];
            ptr_end[0] = '\0';
            length_word = ptr_end - ptr_string;

            if (!word_ok)
            {
                if ((save_end != '\0')
                    || (weechat_config_integer (weechat_aspell_config_check_real_time)))
                {
                    word_ok = weechat_aspell_check_word (ptr_speller_buffer,
                                                         ptr_string);
                    if (!word_ok && (input_pos >= word_start_pos))
                    {
                        /*
                         * if word is misspelled and that cursor is after
                         * the beginning of this word, save the word (we will
                         * look for suggestions after this loop)
                         */
                        if (word_for_suggestions)
                            free (word_for_suggestions);
                        word_for_suggestions = strdup (ptr_string);
                    }
                }
                else
                    word_ok = 1;
            }

            /* add error color */
            if (!word_ok)
            {
                strcpy (result + index_result, color_error);
                index_result += length_color_error;
            }

            /* add word */
            strcpy (result + index_result, ptr_string);
            index_result += length_word;

            /* add normal color (after misspelled word) */
            if (!word_ok)
            {
                strcpy (result + index_result, color_normal);
                index_result += length_color_normal;
            }

            if (save_end == '\0')
                break;

            ptr_end[0] = save_end;
            ptr_string = ptr_end;
            current_pos = word_end_pos + 1;
        }
        result[index_result] = '\0';
    }

    /* save old suggestions in buffer */
    ptr_suggestions = weechat_buffer_get_string (buffer,
                                                 "localvar_aspell_suggest");
    old_suggestions = (ptr_suggestions) ? strdup (ptr_suggestions) : NULL;

    /* if there is a misspelled word, get suggestions and set them in buffer */
    if (word_for_suggestions)
    {
        suggestions = weechat_aspell_get_suggestions (ptr_speller_buffer,
                                                      word_for_suggestions);
        if (suggestions)
        {
            length = strlen (word_for_suggestions) + 1 /* ":" */
                + strlen (suggestions) + 1;
            word_and_suggestions = malloc (length);
            if (word_and_suggestions)
            {
                snprintf (word_and_suggestions, length, "%s:%s",
                          word_for_suggestions, suggestions);
                weechat_buffer_set (buffer, "localvar_set_aspell_suggest",
                                    word_and_suggestions);
                free (word_and_suggestions);
            }
            else
            {
                weechat_buffer_set (buffer, "localvar_del_aspell_suggest", "");
            }
            free (suggestions);
        }
        else
        {
            weechat_buffer_set (buffer, "localvar_del_aspell_suggest", "");
        }
        free (word_for_suggestions);
    }
    else
    {
        weechat_buffer_set (buffer, "localvar_del_aspell_suggest", "");
    }

    /*
     * if suggestions have changed, update the bar item
     * and send signal "aspell_suggest"
     */
    ptr_suggestions = weechat_buffer_get_string (buffer,
                                                 "localvar_aspell_suggest");
    if ((old_suggestions && !ptr_suggestions)
        || (!old_suggestions && ptr_suggestions)
        || (old_suggestions && ptr_suggestions
            && (strcmp (old_suggestions, ptr_suggestions) != 0)))
    {
        weechat_bar_item_update ("aspell_suggest");
        (void) weechat_hook_signal_send ("aspell_suggest",
                                         WEECHAT_HOOK_SIGNAL_POINTER, buffer);
    }
    if (old_suggestions)
        free (old_suggestions);

    if (!result)
        return NULL;

    ptr_speller_buffer->modifier_result = strdup (result);

    return result;
}