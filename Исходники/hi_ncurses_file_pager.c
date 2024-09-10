void hi_ncurses_fpager_redraw(hi_ncurses_fpager *pager)
{
  int x, y;
  unsigned char val;
  off_t offset;
  char buffer[256];
  hi_diff_hunk *hunk;
  werase(pager->window);
  gboolean diff;
  void *highlighter_data = NULL;
  hi_ncurses_highlight *highlighter;
  enum hi_ncurses_colour colour;
  char format_str[256];
  int bytes;
  enum hi_ncurses_colour *highlight_colours = NULL;
  
  highlighter = pager->highlighter;
  
  if ((highlighter != NULL) && (highlighter->begin_func != NULL))
  {
    highlighter_data = highlighter->begin_func(pager->file);
  }
  
  /* Make the pager we're selected highlighted */
  if (pager == pager->curses->focused_pager)
    wattron(pager->window, A_REVERSE);
  
  box(pager->window, ACS_VLINE, ACS_HLINE);

  if (pager == pager->curses->focused_pager)
    wattroff(pager->window, A_REVERSE);
  
  mvwprintw(pager->window, pager->height-1, 2," %s ", pager->file->filename);  
  
  snprintf(format_str,256,pager->location_mode->constructor_string, pager->bytes_in_location);

  bytes = (pager->set_bytes_per_row == 0 ? pager->bytes_per_row : pager->set_bytes_per_row);
  if (bytes > pager->bytes_per_row)
  {
    bytes = pager->bytes_per_row;
  }
  
  highlight_colours = calloc((pager->height-2)*bytes, sizeof(enum hi_ncurses_colour));
  if ((highlighter != NULL) && (highlighter->block_func != NULL))
  {
	  highlighter->block_func(pager->file, pager->offset, (pager->height-2)*bytes, highlight_colours);
  }


  for (y=0; y< pager->height-2; y++)
  {
    for (x=0; x<bytes; x++)
    {
      offset = pager->offset+x+(pager->set_bytes_per_row == 0 ? pager->bytes_per_row*y : pager->set_bytes_per_row*y);

      if (offset < pager->file->size)
      {
          if (x == 0)
          {

            
            snprintf(buffer, 256, format_str, (unsigned int) offset);
            wmove(pager->window, y+1,2);
            waddstr(pager->window, buffer);
            

          }
          val = pager->file->memory[offset];
        
          diff = FALSE;
          if (pager->diff)
          {
            hunk = hi_diff_get_hunk(pager->diff, pager->file, offset);
            if (hunk != NULL && hunk->type == HI_DIFF_TYPE_DIFF)
            {
              diff = TRUE;
            }
            
          }
        
          if (TRUE == diff)
            wattron(pager->window, A_REVERSE);
          
          colour = highlight_colours[offset-pager->offset];
          if ((highlighter != NULL) && (highlighter->highlight_func != NULL))
          {
            colour = highlighter->highlight_func(pager->file, offset, val, highlighter_data);
            
          }

        
          if (colour != hi_ncurses_colour_normal)
          {
            wcolor_set(pager->window, colour, NULL);
          }
        
          /* Display byte */
          pager->display_mode->display_byte_func(pager, y+1, 3+pager->bytes_in_location, x, offset, val);
 
          if (colour != hi_ncurses_colour_normal)
          {
            wcolor_set(pager->window, hi_ncurses_colour_normal,NULL);
          }
          if (TRUE == diff)
            wattroff(pager->window, A_REVERSE);
            
      }
    }
  
  }
  if ((highlighter != NULL) && (highlighter->end_func != NULL))
  {
       highlighter->end_func(highlighter_data);
  }

  free(highlight_colours);
      
  wrefresh(pager->window);
}