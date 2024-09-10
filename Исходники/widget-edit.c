/**
 * Handle a keydown callback
 *
 * @param __edit - edit received a callback
 * @param __ch - received character
 * @return zero if callback hasn't handled received character
 */
static int
edit_keydown (w_edit_t *__edit, wint_t __ch)
{
  _WIDGET_CALL_USER_CALLBACK (__edit, keydown, __edit, __ch);

  size_t spos, sscrolled;
  wchar_t *sbuffer = NULL;
  BOOL rollback_changes = FALSE, sshaded, reject_suffix = FALSE;

  /* Save data for rollback if validation failed */
  spos      = __edit->caret_pos;
  sscrolled = __edit->scrolled;
  sshaded   = __edit->shaded;

  /* Buffer may be unallocated, so we need this checking */
  if (__edit->text.data)
    {
      sbuffer = wcsdup (__edit->text.data);
    }

  switch (__ch)
    {
      /* Navigation */
    case KEY_LEFT:
      if (__edit->caret_pos > 0)
        {
          --__edit->caret_pos;
        }
      __edit->shaded = FALSE;
      break;
    case KEY_RIGHT:
      if (__edit->caret_pos < wcslen (__edit->text.data))
        {
          ++__edit->caret_pos;
        }
      __edit->shaded = FALSE;
      break;
    case KEY_HOME:
      /*
       * NOTE: IMHO using this stupid cycle is much more convenient
       *       than hard-core patching edit_validate_scrolling().
       *       If you'll find a grateful solving of this
       *       problem - you are welcome :)
       */
      while (__edit->caret_pos > 0)
        {
          __edit->caret_pos--;
          edit_validate_scrolling (__edit);
        }
      __edit->shaded = FALSE;
      break;
    case KEY_END:
      while (__edit->caret_pos < wcslen (__edit->text.data))
        {
          __edit->caret_pos++;
          edit_validate_scrolling (__edit);
        }
      __edit->shaded = FALSE;
      break;

    case KEY_DELETE:
    case KEY_BACKSPACE:
      {
        size_t i, n;
        n = wcslen (__edit->text.data);

        /* If pressed key is a `backspace`, we should */
        /* move caret left by one position. */
        if (__ch == KEY_BACKSPACE)
          {
            wchar_t c = __edit->text.data[n - 1], nch;
            int ch_width = wcwidth (c), dummy;

            /* Caret is already in zero position. */
            /* No chars to delete */
            if (!__edit->caret_pos)
              {
                break;
              }

            if (__edit->scrolled > 0)
              {
                /* This dark spell is needed to make cursor to */
                /* at his old position */

                /*
                 * TODO: There is some troubles in this stuff
                 */
                while (__edit->scrolled > 0)
                  {
                    nch = __edit->text.data[__edit->scrolled];
                    dummy = wcwidth (nch);
                    if (ch_width - dummy < 0)
                      {
                        break;
                      }
                    ch_width -= dummy;
                    --__edit->scrolled;
                  }
              }
            --__edit->caret_pos;
          }
        else
          {
            /* There are no chars at the right side from cursor */
            /* so, there are no chars to delete */
            if (__edit->caret_pos == n)
            {
              reject_suffix = TRUE;
              widget_redraw (WIDGET (__edit));
              break;
            }
          }

        /* Shift text */
        for (i = __edit->caret_pos; i < n - 1; i++)
          {
            __edit->text.data[i] = __edit->text.data[i + 1];
          }

        /* Set new null-terminator */
        __edit->text.data[n - 1] = 0;

        /* Send validating message */
        if (CALL_CHECKVALIDNESS (__edit))
          {
            /* We need rollback changes */
            rollback_changes = TRUE;
          }

        __edit->shaded = FALSE;
      }

      break;

    case KEY_ESC:
      /* If user hits Escape button when there is guessed suffix of string */
      /* we should cancel this guessing */
      /* And if user hits Escape button when there is no suffix, */
      /* we should do nothing */
      if (__edit->suffix)
        {
          __edit->suffix = NULL;
          widget_redraw (WIDGET (__edit));
          return TRUE;
        }
      else
        {
          return FALSE;
        }
      break;

    case KEY_RETURN:
      /* If user hits Return button when there is guessed suffix of string */
      /* we should accept guessing string to main buffer */
      /* And if user hits Return button when there is no suffix, */
      /* we should do nothing */
      if (__edit->suffix)
        {
          size_t len = wcslen (__edit->text.data),
                 suff_len = wcslen (__edit->suffix);

          /* Realloc buffer if needed */
          if (len + suff_len >= __edit->text.allocated)
            {
              __edit->text.data = realloc (__edit->text.data,
                                       (len + suff_len + 1) * sizeof (wchar_t));
              __edit->text.allocated = len + suff_len;
            }

          /* Append auto-guessed suffix to main text buffer */
          wcscat (__edit->text.data, __edit->suffix);

          /* Move caret to end of text */
          __edit->caret_pos = len + suff_len;
          edit_validate_scrolling (__edit);

          __edit->suffix = NULL;
          widget_redraw (WIDGET (__edit));
          return TRUE;
        }
      else
        {
          return FALSE;
        }
      break;

    default:

#ifdef SCREEN_NCURSESW
      /*
       * FIXME: We'd better not use specific stuff of terminal
       *        handling in widgets.
       */
      if (is_ncurses_funckey (__ch))
        {
          return FALSE;
        }
#endif

      if (iswprint (__ch))
        {
          /* Character is printable, so we have to handle this */
          /* callback ourselves */

          size_t i, len;

          /* Is edit in shaded state? */
          if (__edit->shaded)
            {
              /* If edit is in shaded state, we should clear text */
              /* and move caret to the beginning. */
              /* We should also reset count of scrolled characters */
              /* and finally, exit edit from shaded state. */

              wcscpy (__edit->text.data, L"");
              __edit->caret_pos = __edit->scrolled = 0;
              __edit->shaded = FALSE;
            }

          len = wcslen (__edit->text.data);

          /* Synchronize buffer to make sure that there is */
          /* enough memory to append character */
          edit_sync_buffer (__edit);

          /* Shift buffer */
          for (i = len; i > __edit->caret_pos; --i)
            {
              __edit->text.data[i] = __edit->text.data[i - 1];
            }

          /* Insert new character into text */
          __edit->text.data[__edit->caret_pos] = __ch;
          __edit->text.data[len + 1] = 0;

          /* Move caret to new position */
          __edit->caret_pos++;

          /* Send validating message */
          if (CALL_CHECKVALIDNESS (__edit))
            {
              /* We need rollback changes */
              rollback_changes = TRUE;
            }
        }
      else
        {
          return FALSE;
        }
    }

  /* If validator rejected buffer.. */
  if (rollback_changes)
    {
      /* ..roll-back changes */
      __edit->caret_pos = spos;
      __edit->scrolled  = sscrolled;
      __edit->shaded    = sshaded;

      /* Reject renewed buffer */
      SAFE_FREE (__edit->text.data);
      if (sbuffer)
        {
          __edit->text.data = sbuffer;
          __edit->text.allocated = wcslen (sbuffer) + 1;

          /* Need this to prevent freeing buffer later */
          sbuffer = NULL;
        }
      else
        {
          __edit->text.allocated = 0;
        }
    }
  else
    {
      if (!reject_suffix)
        {
          make_guessing (__edit);
        }
      else
        {
          __edit->suffix = NULL;
        }
    }

  SAFE_FREE (sbuffer);

  edit_validate_scrolling (__edit);
  widget_redraw (WIDGET (__edit));

  return TRUE;
}