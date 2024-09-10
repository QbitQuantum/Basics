/**
 * clutter_win32_handle_event:
 * @msg: A pointer to a structure describing a Win32 message.
 *
 * This function processes a single Win32 message. It can be used to
 * hook into external windows message processing (for example, a GDK
 * filter function).
 *
 * If clutter_win32_disable_event_retrieval() has been called, you must
 * let this function process events to update Clutter's internal state.
 *
 * Return value: %TRUE if the message was handled entirely by Clutter
 * and no further processing (such as calling the default window
 * procedure) should take place. %FALSE is returned if is the message
 * was not handled at all or if Clutter expects processing to take
 * place.
 *
 * Since: 1.6
 */
gboolean
clutter_win32_handle_event (const MSG *msg)
{
  ClutterBackendWin32  *backend_win32;
  ClutterStageWin32    *stage_win32;
  ClutterDeviceManager *manager;
  ClutterInputDevice   *core_pointer, *core_keyboard;
  ClutterStage         *stage;
  ClutterStageWindow   *impl;
  gboolean              return_value = FALSE;

  stage = clutter_win32_get_stage_from_window (msg->hwnd);

  /* Ignore any messages for windows which we don't have a stage for */
  if (stage == NULL)
    return FALSE;

  impl = _clutter_stage_get_window (stage);
  stage_win32 = CLUTTER_STAGE_WIN32 (impl);
  backend_win32 = stage_win32->backend;

  manager = clutter_device_manager_get_default ();
  core_pointer =
    clutter_device_manager_get_core_device (manager, CLUTTER_POINTER_DEVICE);
  core_keyboard =
    clutter_device_manager_get_core_device (manager, CLUTTER_KEYBOARD_DEVICE);

  switch (msg->message)
    {
    case WM_SIZE:
      if (!stage_win32->is_foreign_win
	  /* Ignore size changes resulting from the stage being
	     minimized - otherwise the window size will be set to
	     0,0 */
	  && msg->wParam != SIZE_MINIMIZED)
	{
	  WORD new_width = LOWORD (msg->lParam);
	  WORD new_height = HIWORD (msg->lParam);
	  gfloat old_width, old_height;

	  clutter_actor_get_size (CLUTTER_ACTOR (stage),
				  &old_width, &old_height);

	  if (new_width != old_width || new_height != old_height)
	    clutter_actor_set_size (CLUTTER_ACTOR (stage),
				    new_width, new_height);
	}
      break;

    case WM_SHOWWINDOW:
      if (msg->wParam)
	clutter_stage_win32_map (stage_win32);
      else
	clutter_stage_win32_unmap (stage_win32);
      break;

    case WM_ACTIVATE:
      if (msg->wParam == WA_INACTIVE)
        {
          if (stage_win32->state & CLUTTER_STAGE_STATE_ACTIVATED)
            {
              ClutterEvent *event = clutter_event_new (CLUTTER_STAGE_STATE);

              stage_win32->state &= ~CLUTTER_STAGE_STATE_ACTIVATED;

              event->any.stage = stage;
              event->stage_state.changed_mask = CLUTTER_STAGE_STATE_ACTIVATED;
              event->stage_state.new_state = stage_win32->state;

              take_and_queue_event (event);
            }
        }
      else if (!(stage_win32->state & CLUTTER_STAGE_STATE_ACTIVATED))
        {
          ClutterEvent *event = clutter_event_new (CLUTTER_STAGE_STATE);

          stage_win32->state |= CLUTTER_STAGE_STATE_ACTIVATED;

          event->any.stage = stage;
          event->stage_state.changed_mask = CLUTTER_STAGE_STATE_ACTIVATED;
          event->stage_state.new_state = stage_win32->state;

          take_and_queue_event (event);
        }
      break;

    case WM_PAINT:
      CLUTTER_NOTE (MULTISTAGE, "expose for stage:%p, redrawing", stage);
      clutter_redraw (stage);
      break;

    case WM_DESTROY:
      {
        ClutterEvent *event = clutter_event_new (CLUTTER_DESTROY_NOTIFY);

        CLUTTER_NOTE (EVENT, "WM_DESTROY");

        event->any.stage = stage;

        take_and_queue_event (event);
      }
      break;

    case WM_CLOSE:
      {
        ClutterEvent *event = clutter_event_new (CLUTTER_DELETE);

        CLUTTER_NOTE (EVENT, "WM_CLOSE");

        event->any.stage = stage;

        take_and_queue_event (event);

        /* The default window proc will destroy the window so we want to
           prevent this to allow applications to optionally destroy the
           window themselves */
        return_value = TRUE;
      }
      break;

    case WM_LBUTTONDOWN:
      make_button_event (msg, stage, 1, 1, FALSE, core_pointer);
      break;

    case WM_MBUTTONDOWN:
      make_button_event (msg, stage, 2, 1, FALSE, core_pointer);
      break;

    case WM_RBUTTONDOWN:
      make_button_event (msg, stage, 3, 1, FALSE, core_pointer);
      break;

    case WM_LBUTTONUP:
      make_button_event (msg, stage, 1, 1, TRUE, core_pointer);
      break;

    case WM_MBUTTONUP:
      make_button_event (msg, stage, 2, 1, TRUE, core_pointer);
      break;

    case WM_RBUTTONUP:
      make_button_event (msg, stage, 3, 1, TRUE, core_pointer);
      break;

    case WM_LBUTTONDBLCLK:
      make_button_event (msg, stage, 1, 2, FALSE, core_pointer);
      break;

    case WM_MBUTTONDBLCLK:
      make_button_event (msg, stage, 2, 2, FALSE, core_pointer);
      break;

    case WM_RBUTTONDBLCLK:
      make_button_event (msg, stage, 3, 2, FALSE, core_pointer);
      break;

    case WM_MOUSEWHEEL:
      stage_win32->scroll_pos += (SHORT) HIWORD (msg->wParam);

      while (abs (stage_win32->scroll_pos) >= WHEEL_DELTA)
        {
          ClutterEvent *event = clutter_event_new (CLUTTER_SCROLL);
          POINT pt;

          event->scroll.time = msg->time;
          event->scroll.modifier_state =
            get_modifier_state (LOWORD (msg->wParam));
          event->any.stage = stage;

          clutter_event_set_device (event, core_pointer);

          /* conversion to window coordinates is required */
          pt.x = GET_X_LPARAM (msg->lParam);
          pt.y = GET_Y_LPARAM (msg->lParam);
          ScreenToClient (msg->hwnd, &pt);
          event->scroll.x = pt.x;
          event->scroll.y = pt.y;

          if (stage_win32->scroll_pos > 0)
            {
              event->scroll.direction = CLUTTER_SCROLL_UP;
              stage_win32->scroll_pos -= WHEEL_DELTA;
            }
          else
            {
              event->scroll.direction = CLUTTER_SCROLL_DOWN;
              stage_win32->scroll_pos += WHEEL_DELTA;
            }

          take_and_queue_event (event);
        }
      break;

    case WM_MOUSEMOVE:
      {
        ClutterEvent *event = clutter_event_new (CLUTTER_MOTION);

        event->motion.time = msg->time;
        event->motion.x = GET_X_LPARAM (msg->lParam);
        event->motion.y = GET_Y_LPARAM (msg->lParam);
        event->motion.modifier_state = get_modifier_state (msg->wParam);
        event->any.stage = stage;

        clutter_event_set_device (event, core_pointer);

        /* We need to start tracking when the mouse enters the stage if
           we're not already */
        if (!stage_win32->tracking_mouse)
          {
            ClutterEvent *crossing = clutter_event_new (CLUTTER_ENTER);
            TRACKMOUSEEVENT tmevent;

            tmevent.cbSize = sizeof (tmevent);
            tmevent.dwFlags = TME_LEAVE;
            tmevent.hwndTrack = stage_win32->hwnd;
            TrackMouseEvent (&tmevent);

            event->crossing.time = msg->time;
            event->crossing.x = event->motion.x;
            event->crossing.y = event->motion.y;
            event->crossing.stage = stage;
            event->crossing.source = CLUTTER_ACTOR (stage);
            event->crossing.related = NULL;

            clutter_event_set_device (event, core_pointer);

            /* we entered the stage */
            _clutter_stage_add_device (stage, event->crossing.device);

            take_and_queue_event (crossing);

            stage_win32->tracking_mouse = TRUE;
          }

        take_and_queue_event (event);
      }
      break;

    case WM_MOUSELEAVE:
      {
        ClutterEvent *event = clutter_event_new (CLUTTER_LEAVE);

        event->crossing.time = msg->time;
        event->crossing.x = msg->pt.x;
        event->crossing.y = msg->pt.y;
        event->crossing.stage = stage;
        event->crossing.source = CLUTTER_ACTOR (stage);
        event->crossing.related = NULL;

        clutter_event_set_device (event, core_pointer);

        /* we left the stage */
        _clutter_stage_remove_device (stage, core_pointer);

        /* When we get a leave message the mouse tracking is
           automatically cancelled so we'll need to start it again when
           the mouse next enters the window */
        stage_win32->tracking_mouse = FALSE;

        take_and_queue_event (event);
      }
      break;

    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
      {
        ClutterEvent *event = clutter_event_new (CLUTTER_EVENT_NONE);
	int scan_code = (msg->lParam >> 16) & 0xff;
	int min = 0, max = CLUTTER_WIN32_KEY_MAP_SIZE, mid;
	BYTE key_states[256];

	/* Get the keyboard modifier states. GetKeyboardState
	   conveniently gets the key state that was current when the
	   last keyboard message read was generated */
	GetKeyboardState(key_states);

	/* Binary chop to check if we have a direct mapping for this
	   key code */
	while (min < max)
	  {
	    mid = (min + max) / 2;
	    if (clutter_win32_key_map[mid].win_sym == msg->wParam)
	      {
		event->key.keyval = clutter_win32_key_map[mid].clutter_sym;
		event->key.unicode_value = 0;
		break;
	      }
	    else if (clutter_win32_key_map[mid].win_sym < msg->wParam)
	      min = mid + 1;
	    else
	      max = mid;
	  }

	/* If we don't have a direct mapping then try getting the
	   unicode value of the key sym */
	if (min >= max)
	  {
	    WCHAR ch;
	    BYTE shift_state[256];

	    /* Translate to a Unicode value, but only take into
	       account the shift key. That way Ctrl+Shift+C will
	       generate a capital C virtual key code with a zero
	       unicode value for example */
	    memset (shift_state, 0, 256);
	    shift_state[VK_SHIFT] = key_states[VK_SHIFT];
	    shift_state[VK_LSHIFT] = key_states[VK_LSHIFT];
	    shift_state[VK_RSHIFT] = key_states[VK_RSHIFT];
	    shift_state[VK_CAPITAL] = key_states[VK_CAPITAL];

	    if (ToUnicode (msg->wParam, scan_code,
			   shift_state, &ch, 1, 0) == 1
		/* The codes in this range directly match the Latin 1
		   codes so we can just use the Unicode value as the
		   key sym */
		&& ch >= 0x20 && ch <= 0xff)
	      event->key.keyval = ch;
	    else
	      /* Otherwise we don't know what the key means but the
		 application might be able to do something with the
		 scan code so we might as well still generate the
		 event */
	      event->key.keyval = CLUTTER_KEY_VoidSymbol;

	    /* Get the unicode value of the keypress again using the
	       full modifier state */
	    if (ToUnicode (msg->wParam, scan_code,
			   key_states, &ch, 1, 0) == 1)
		event->key.unicode_value = ch;
	    else
		event->key.unicode_value = 0;
	  }

	event->key.type = msg->message == WM_KEYDOWN
	  || msg->message == WM_SYSKEYDOWN
	  ? CLUTTER_KEY_PRESS : CLUTTER_KEY_RELEASE;
	event->key.time = msg->time;
	event->key.modifier_state = get_key_modifier_state (key_states);
	event->key.hardware_keycode = scan_code;
        event->any.stage = stage;

        clutter_event_set_device (event, core_keyboard);

        take_and_queue_event (event);
      }
      break;

    case WM_GETMINMAXINFO:
      {
	MINMAXINFO *min_max_info = (MINMAXINFO *) msg->lParam;
	_clutter_stage_win32_get_min_max_info (stage_win32, min_max_info);
        return_value = TRUE;
      }
      break;

    case WM_SETCURSOR:
      /* If the cursor is in the window's client area and the stage's
         cursor should be invisible then we'll set a blank cursor
         instead */
      if (LOWORD (msg->lParam) == HTCLIENT && !stage_win32->is_cursor_visible)
        {
          return_value = TRUE;
          _clutter_stage_win32_update_cursor (stage_win32);
        }
      break;
    }

  return return_value;
}