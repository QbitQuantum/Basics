void uiview_search_addch(int ch)
{
  if(ispunct(ch) || isalnum(ch) || (ch == ' '))
  {
    if(searchstr_pos < searchstr_len)
    {
      memmove(&(searchstr[searchstr_pos + 1]),
              &(searchstr[searchstr_pos]), searchstr_len - searchstr_pos);
    }
    searchstr[searchstr_pos] = (char)ch;
    searchstr_pos++;
    searchstr_len++;
    search_selected = 0;
  }
  else
  {
    switch(ch)
    {
      case '\n':
        /* Play selected track */
        {
          track_t *track = g_slist_nth_data(search_results, search_selected);
          if(track)
          {
            list_enqueue_insert_first_track(track);
            model_next();
          }
          uiview_set_search(0);
        }
        break;

      case KEY_IC:
        /* Enqueue selected track */
        {
          track_t *track = g_slist_nth_data(search_results, search_selected);
          if(track)
          {
            list_enqueue_insert_first_track(track);
          }
        }
        break;

      case KEY_LEFT:
        if(searchstr_pos > 0)
        {
          searchstr_pos--;
        }
        break;

      case KEY_RIGHT:
        if(searchstr_pos < searchstr_len)
        {
          searchstr_pos++;
        }
        break;

      case KEY_UP:
        if(search_selected > 0)
        {
          search_selected--;
        }
        break;

      case KEY_DOWN:
        if(search_selected < ((int)g_slist_length(search_results) - 1))
        {
          search_selected++;
        }
        break;

      case KEY_BACKSPACE:
        if(searchstr_pos > 0)
        {
          if(searchstr_pos < searchstr_len)
          {
            memmove(&(searchstr[searchstr_pos - 1]),
                    &(searchstr[searchstr_pos]), 
                    searchstr_len - searchstr_pos);
          }
          searchstr_pos--;
          searchstr_len--;
          searchstr[searchstr_len] = '\0';
          search_selected = 0;
        }
        break;

      case 27:
        uiview_set_search(0);
        break;

      default:
        break;
    }
  }
}