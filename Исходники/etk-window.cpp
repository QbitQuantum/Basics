void
EBePrivateWin::DispatchMessage(BMessage *bMsg, BHandler *handler)
{
	bool handled = true;

	if(bMsg->what == 'etk_')
	{
		int32 what = 0;
		bMsg->FindInt32("etk:what", &what);

		switch(what)
		{
			case ETK_BEOS_QUIT:
				doQuit = true;
				PostMessage(B_QUIT_REQUESTED);
				break;

			case ETK_BEOS_CONTACT_TO:
				{
					fContactor = EMessenger();
					const char *buffer = NULL;
					ssize_t size = -1;
					if(bMsg->FindData("etk:messenger", B_ANY_TYPE, (const void**)&buffer, &size) != B_OK) break;
					if(buffer == NULL || size <= 0) break;
					fContactor.Unflatten(buffer, (size_t)size);
				}
				break;

			case ETK_BEOS_SET_BACKGROUND:
				{
					rgb_color bkColor;
					if(bMsg->FindInt32("background", (int32*)&bkColor) != B_OK) break;
					fTopView->SetViewColor(bkColor);
					fTopView->Invalidate();
				}
				break;

			case ETK_BEOS_SET_LOOK:
				{
					int8 look;
					if(bMsg->FindInt8("look", &look) != B_OK) break;
					switch((e_window_look)look)
					{
						case E_BORDERED_WINDOW_LOOK:
							SetLook(B_BORDERED_WINDOW_LOOK);
							break;

						case E_NO_BORDER_WINDOW_LOOK:
							SetLook(B_NO_BORDER_WINDOW_LOOK);
							break;

						case E_TITLED_WINDOW_LOOK:
							SetLook(B_TITLED_WINDOW_LOOK);
							break;

						case E_DOCUMENT_WINDOW_LOOK:
							SetLook(B_DOCUMENT_WINDOW_LOOK);
							break;

						case E_MODAL_WINDOW_LOOK:
							SetLook(B_MODAL_WINDOW_LOOK);
							break;

						case E_FLOATING_WINDOW_LOOK:
							SetLook(B_FLOATING_WINDOW_LOOK);
							break;

						default:
							break;
					}
				}
				break;

			case ETK_BEOS_SET_TITLE:
				{
					const char *title = NULL;
					if(bMsg->FindString("title", &title) != B_OK) break;
					SetTitle(title);
				}
				break;

			case ETK_BEOS_SET_WORKSPACES:
				{
					uint32 workspaces = 0;
					if(bMsg->FindInt32("workspaces", (int32*)&workspaces) != B_OK) break;
					if(workspaces == 0) workspaces = current_workspace() + 1;
					SetWorkspaces(workspaces);
				}
				break;

			case ETK_BEOS_GET_WORKSPACES:
				{
					uint32 workspaces = Workspaces();
					bMsg->AddInt32("workspaces", *((int32*)&workspaces));
				}
				break;

			case ETK_BEOS_ICONIFY:
				if(!IsMinimized()) Minimize(true);
				break;

			case ETK_BEOS_SHOW:
				if(IsHidden())
				{
					uint32 oldFlags = Flags();
					SetFlags(oldFlags | B_AVOID_FOCUS);
					Show();
					if(Look() != B_NO_BORDER_WINDOW_LOOK) SetFlags(oldFlags);
				}
				break;

			case ETK_BEOS_HIDE:
				if(!IsHidden()) Hide();
				break;

			case ETK_BEOS_RAISE:
				if(!IsFront())
				{
					uint32 oldFlags = Flags();
					SetFlags(oldFlags | B_AVOID_FOCUS);
					Activate(true);
					if(Look() != B_NO_BORDER_WINDOW_LOOK) SetFlags(oldFlags);
				}
				break;

			case ETK_BEOS_LOWER:
				{
					BHandler *_frontWin = NULL;
					if(bMsg->FindPointer("front", (void**)&_frontWin) != B_OK) break;
					BWindow *frontWin = e_cast_as(_frontWin, BWindow);
					if(frontWin == NULL) break;
					SendBehind(frontWin);
					bMsg->AddBool("done", true);
				}
				break;

			case ETK_BEOS_ACTIVATE:
				{
					bool state;
					if(bMsg->FindBool("state", &state) != B_OK || state == IsActive()) break;
					Activate(state);
				}
				break;

			case ETK_BEOS_GET_ACTIVATED_STATE:
				bMsg->AddBool("state", IsActive());
				break;

			case ETK_BEOS_MOVE_RESIZE:
				{
					if(bMsg->HasPoint("where"))
					{
						BPoint pt;
						if(bMsg->FindPoint("where", &pt) == B_OK) MoveTo(pt);
					}

					if(bMsg->HasFloat("width") && bMsg->HasFloat("height"))
					{
						float w = -1, h = -1;
						bMsg->FindFloat("width", &w);
						bMsg->FindFloat("height", &h);
						if(w < 0 || h < 0) break;
						ResizeTo(w, h);
					}
				}
				break;

			case ETK_BEOS_DRAW_BITMAP:
				{
					BBitmap *bitmap = NULL;
					BRect srcRect, destRect;
					const ERegion *clipping = NULL;

					if(bMsg->FindPointer("bitmap", (void**)&bitmap) != B_OK || bitmap == NULL) break;
					bMsg->FindRect("src", &srcRect);
					bMsg->FindRect("dest", &destRect);
					if(srcRect.IsValid() == false || destRect.IsValid() == false) break;
					bMsg->FindPointer("clipping", (void**)&clipping); 

					BRegion beRegion;
					__etk_convert_region(clipping, &beRegion, fTopView->Bounds());
					fTopView->ConstrainClippingRegion(&beRegion);
					fTopView->DrawBitmap(bitmap, srcRect, destRect);
				}
				break;

			case ETK_BEOS_GRAB_MOUSE:
			case ETK_BEOS_UNGRAB_MOUSE:
				{
					uint32 options = (what == ETK_BEOS_GRAB_MOUSE ? B_LOCK_WINDOW_FOCUS : 0);
					if(fTopView->SetEventMask(B_POINTER_EVENTS, options) != B_OK) break;
					bMsg->AddBool("state", what == ETK_BEOS_GRAB_MOUSE);
				}
				break;

			case ETK_BEOS_GRAB_KEYBOARD:
			case ETK_BEOS_UNGRAB_KEYBOARD:
				{
					uint32 options = (what == ETK_BEOS_GRAB_KEYBOARD ? B_LOCK_WINDOW_FOCUS : 0);
					if(fTopView->SetEventMask(B_KEYBOARD_EVENTS, options) != B_OK) break;
					bMsg->AddBool("state", what == ETK_BEOS_GRAB_KEYBOARD);
				}
				break;

			case ETK_BEOS_QUERY_MOUSE:
				{
					BPoint pt;
					uint32 btns = 0;
					fTopView->GetMouse(&pt, &btns, false);
					bMsg->AddInt32("x", (int32)pt.x);
					bMsg->AddInt32("y", (int32)pt.y);
					bMsg->AddInt32("buttons", (int32)btns);
				}
				break;

			case ETK_BEOS_SET_SIZE_LIMITS:
				{
					BRect r;
					if(bMsg->FindRect("limits", &r) != B_OK) break;
					SetSizeLimits(r.left, r.right, r.top, r.bottom);
					bMsg->AddBool("done", true);
				}
				break;

			case ETK_BEOS_GET_SIZE_LIMITS:
				{
					BRect r(-1, -1, -1, -1);
					GetSizeLimits(&(r.left), &(r.right), &(r.top), &(r.bottom));
					bMsg->AddRect("limits", r);
				}
				break;

			default:
				handled = false;
				break;
		}

		if(handled)
		{
			BMessage aMsg(*bMsg);
			bMsg->SendReply(&aMsg);
			return;
		}
	}

	switch(bMsg->what)
	{
		case B_WINDOW_ACTIVATED:
			{
				handled = false;

				if(fContactor.IsValid() == false) break;
				EMessage message(E_WINDOW_ACTIVATED);
				message.AddBool("etk:msg_from_gui", true);
				message.AddInt64("when", e_real_time_clock_usecs());
				fContactor.SendMessage(&message);
			}
			break;

		case B_MOUSE_DOWN:
		case B_MOUSE_UP:
		case B_MOUSE_MOVED:
			{
				if(fContactor.IsValid() == false) break;

				BPoint where;
				int32 buttons = 0;

				bMsg->FindPoint("where", &where);
				if(bMsg->what != B_MOUSE_UP) bMsg->FindInt32("buttons", &buttons);

				int32 clicks = 1;
				if(bMsg->what == B_MOUSE_DOWN)
				{
#if 0
					bMsg->FindInt32("clicks", &clicks);
#else
					bigtime_t eventTime;
					if(bMsg->FindInt64("when", &eventTime) == B_OK)
					{
						if(eventTime - fPrevMouseDownTime <= CLICK_TIMEOUT)
							clicks = (fPrevMouseDownCount += 1);
						else
							clicks = fPrevMouseDownCount = 1;
						fPrevMouseDownTime = eventTime;
					}
#endif
				}

				EMessage message;
				if(bMsg->what == B_MOUSE_DOWN) message.what = E_MOUSE_DOWN;
				else if(bMsg->what == B_MOUSE_UP) message.what = E_MOUSE_UP;
				else message.what = E_MOUSE_MOVED;

				message.AddBool("etk:msg_from_gui", true);
				message.AddInt64("when", e_real_time_clock_usecs());
				if(bMsg->what != B_MOUSE_UP) message.AddInt32("buttons", buttons);
				if(bMsg->what == B_MOUSE_DOWN) message.AddInt32("clicks", clicks);
				message.AddPoint("where", EPoint(where.x, where.y));
				ConvertToScreen(&where);
				message.AddPoint("screen_where", EPoint(where.x, where.y));

				// TODO: modifiers

				message.AddMessenger("etk:msg_for_target", fContactor);

				etk_app->PostMessage(&message);
			}
			break;

		case B_KEY_DOWN:
		case B_KEY_UP:
		case B_UNMAPPED_KEY_DOWN:
		case B_UNMAPPED_KEY_UP:
			{
				if(fContactor.IsValid() == false) break;

				int8 byte[4];
				const char *bytes = NULL;
				int32 numBytes = 0;
				int32 key = 0;
				int32 key_repeat = 0;
				int32 beModifiers = 0;
				eint32 modifiers = 0;

				bMsg->FindInt32("key", &key);
				bMsg->FindInt32("modifiers", &beModifiers);
				bzero(byte, sizeof(int8) * 4);

				if(bMsg->what == B_KEY_DOWN || bMsg->what == B_KEY_UP)
				{
					for(int32 i = 0; i < 3; i++) bMsg->FindInt8("byte", i, &byte[i]);
					if(bMsg->FindString("bytes", &bytes) == B_OK) numBytes = strlen(bytes);
//					if(bMsg->what == B_KEY_DOWN) bMsg->FindInt32("be:key_repeat", &key_repeat);
				}
				else
				{
					etk_beos_get_byte(beModifiers, key, (char*)byte);
				}

				if(beModifiers & B_SHIFT_KEY) modifiers |= E_SHIFT_KEY;
				if(beModifiers & B_CONTROL_KEY) modifiers |= E_CONTROL_KEY;
				if(beModifiers & B_COMMAND_KEY) modifiers |= E_COMMAND_KEY;

				EMessage message;
				if(bMsg->what == B_KEY_DOWN) message.what = E_KEY_DOWN;
				else if(bMsg->what == B_KEY_UP) message.what = E_KEY_UP;
				else if(bMsg->what == B_UNMAPPED_KEY_DOWN) message.what = E_UNMAPPED_KEY_DOWN;
				else message.what = E_UNMAPPED_KEY_UP;

				message.AddBool("etk:msg_from_gui", true);
				message.AddInt64("when", e_real_time_clock_usecs());
				message.AddInt32("key", key);
				message.AddInt32("modifiers", modifiers);

				if(bMsg->what == B_KEY_DOWN || bMsg->what == B_KEY_UP)
				{
					if(bMsg->what == B_KEY_DOWN) message.AddInt32("etk:key_repeat", key_repeat);
					for(int32 i = 0; i < 3; i++) message.AddInt8("byte", byte[i]);
					if(!(numBytes != 1 || *bytes != byte[0]))
					{
						etk_beos_get_byte(beModifiers, key, (char*)byte);
						message.AddString("bytes", (char*)byte);
					}
					else if(numBytes > 0)
					{
						message.AddString("bytes", bytes);
					}
				}
				else if(byte[0] != 0)
				{
					message.AddInt8("byte", byte[0]);
					message.AddString("bytes", (char*)byte);
				}

				message.AddMessenger("etk:msg_for_target", fContactor);

				etk_app->PostMessage(&message);
			}
			break;

		case B_MODIFIERS_CHANGED:
			{
				if(fContactor.IsValid() == false) break;

				eint32 modifiers = 0;
				eint32 old_modifiers = 0;
				int32 beModifiers = 0;
				int32 old_beModifiers = 0;

				bMsg->FindInt32("modifiers", &beModifiers);
				bMsg->FindInt32("be:old_modifiers", &old_beModifiers);

				if(beModifiers & B_SHIFT_KEY) modifiers |= E_SHIFT_KEY;
				if(beModifiers & B_CONTROL_KEY) modifiers |= E_CONTROL_KEY;
				if(beModifiers & B_COMMAND_KEY) modifiers |= E_COMMAND_KEY;

				if(old_beModifiers & B_SHIFT_KEY) old_modifiers |= E_SHIFT_KEY;
				if(old_beModifiers & B_CONTROL_KEY) old_modifiers |= E_CONTROL_KEY;
				if(old_beModifiers & B_COMMAND_KEY) old_modifiers |= E_COMMAND_KEY;

				EMessage message(E_MODIFIERS_CHANGED);

				message.AddBool("etk:msg_from_gui", true);
				message.AddInt64("when", e_real_time_clock_usecs());
				message.AddInt32("modifiers", modifiers);
				message.AddInt32("etk:old_modifiers", old_modifiers);

				message.AddMessenger("etk:msg_for_target", fContactor);

				etk_app->PostMessage(&message);
			}
			break;

		default:
			handled = false;
			break;
	}

	if(!handled) BWindow::DispatchMessage(bMsg, handler);
}