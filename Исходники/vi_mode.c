static int
_rl_vi_change_mbchar_case(int count)
{
  wchar_t wc;
  char mb[MB_LEN_MAX + 1];
  int mb_len;
  mbstate_t ps;

  memset(&ps, 0, sizeof(mbstate_t));
  if (_rl_adjust_point(rl_line_buffer, rl_point, &ps) > 0)
    count--;
  while (count-- && (rl_point < rl_end))
    {
      mbrtowc(&wc, (rl_line_buffer + rl_point),
              (size_t)(rl_end - rl_point), &ps);
      if (iswupper(wc))
	wc = towlower(wc);
      else if (iswlower(wc))
	wc = towupper(wc);
      else
	{
	  /* Just skip over chars neither upper nor lower case */
	  rl_forward_char(1, 0);
	  continue;
	}

      /* Vi is kind of strange here. */
      if (wc)
	{
	  mb_len = wctomb(mb, wc);
	  if (mb_len >= 0)
	    mb[mb_len] = '\0';
	  rl_begin_undo_group();
	  rl_delete(1, 0);
	  rl_insert_text(mb);
	  rl_end_undo_group();
	  rl_vi_check();
	}
      else
        rl_forward_char(1, 0);
    }

  return 0;
}