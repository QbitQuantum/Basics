LRESULT CALLBACK MCWindowProc(HWND hwnd, UINT msg, WPARAM wParam,
                              LPARAM lParam)
{
	static Boolean isactive = True;
	KeySym keysym;
	MCStack *target;
	_Drawable _dw;
	Drawable dw = &_dw;
	dw->type = DC_WINDOW;
	dw->handle.window = (MCSysWindowHandle)hwnd;
	MCScreenDC *pms = (MCScreenDC *)MCscreen;
	MCStack *omousestack = MCmousestackptr;
	uint2 button;
	Boolean down;
	char buffer[XLOOKUPSTRING_SIZE];

	MCPoint t_mouseloc;
	t_mouseloc = MCPointMake(LOWORD(lParam), HIWORD(lParam));

	// IM-2014-01-28: [[ HiDPI ]] Convert screen to logical coords
	t_mouseloc = ((MCScreenDC*)MCscreen)->screentologicalpoint(t_mouseloc);

	// MW-2005-02-20: Seed the SSL random number generator
#ifdef MCSSL
	SeedSSL(msg, wParam, lParam);
#endif

	if (curinfo == NULL)
		curinfo = &dummycurinfo;

	switch (msg)
	{
#ifdef FEATURE_RELAUNCH_SUPPORT
		case WM_COPYDATA:
		{
			LRESULT t_result;
			COPYDATASTRUCT *t_data;
			t_data = (COPYDATASTRUCT *)lParam;

			t_result = 0;
			if (t_data -> dwData == CWM_RELAUNCH)
			{
				MCresult -> clear();

				MCParameter *t_first_parameter = NULL;
				MCParameter *t_current_parameter = NULL;

				extern char *strndup(const char *, unsigned int);
				char *t_command_line = strndup((char *)t_data -> lpData, t_data -> cbData);

				char *sptr = t_command_line;
				while(*sptr)
				{
					if (*sptr == '\\')
						*sptr = '/';
					sptr++;
				}
				sptr = t_command_line;
				while(*sptr)
				{
					char *t_argument;
					int t_argument_length;

					while (isspace(*sptr))
						sptr++;

					t_argument_length = 0;
					if (*sptr == '"')
					{
						t_argument = ++sptr;
						while (*sptr && *sptr != '"')
						{
							sptr++;
							t_argument_length += 1;
						}
					}
					else
					{
						t_argument = sptr;
						while(*sptr && !isspace(*sptr))
						{
							sptr++;
							t_argument_length += 1;
						}
					}

					if (t_argument_length != 0)
					{
						MCParameter *t_parameter;
						MCString t_param;
						t_param . set(t_argument, t_argument_length);
						t_parameter = new MCParameter(t_param);
						if (t_first_parameter == NULL)
							t_first_parameter = t_parameter;
						else
							t_current_parameter -> setnext(t_parameter);
						t_current_parameter = t_parameter;
					}

					if (*sptr)
						sptr++;
				}

				if (MCdispatcher -> gethome() -> message(MCM_relaunch, t_first_parameter, False, True) != ES_NORMAL)
					t_result = 0;
				else
				{
					MCExecPoint t_ep;
					MCresult -> fetch(t_ep);
					
					if (t_ep . getsvalue() == "background")
						t_result = (LRESULT)HWND_BOTTOM;
					else
						t_result = MCdefaultstackptr -> getwindow() == NULL ? (LRESULT)HWND_BOTTOM : (LRESULT)(MCdefaultstackptr -> getwindow() -> handle . window);
				}

				while(t_first_parameter != NULL)
				{
					MCParameter *t_next;
					t_next = t_first_parameter -> getnext();
					delete t_first_parameter;
					t_first_parameter = t_next;
				}

				free(t_command_line);

				MCresult -> clear();
			}

			return t_result;
		}
#endif
	case CWM_TASKBAR_NOTIFICATION:
		((MCScreenDC *)MCscreen) -> processtaskbarnotify(hwnd, wParam, lParam);
		break;

	case WM_DISPLAYCHANGE:
	case WM_SETTINGCHANGE:
	{
		if (hwnd != ((MCScreenDC *)MCscreen) -> getinvisiblewindow())
			break;

		((MCScreenDC *)MCscreen) -> processdesktopchanged(true);
	}
	break;
	case WM_PALETTECHANGED:
		dw->handle.window = (MCSysWindowHandle)wParam;
		if (MCdispatcher->findstackd(dw) == NULL)
		{
			dw->handle.window = (MCSysWindowHandle)hwnd;
			MCStack *sptr = MCdispatcher->findstackd(dw);
			if (sptr != NULL)
				sptr->dirtyall();
			}
		break;
	case WM_PAINT:
		{
			MCStack *t_stack;
			t_stack = MCdispatcher -> findstackd(dw);
			if (t_stack != nil)
				t_stack -> onpaint();
		}
		break;
	case WM_SETFOCUS: //FocusIn
		if (curinfo->dispatch)
		{
			if (MCtracewindow == DNULL || hwnd != (HWND)MCtracewindow->handle.window)
			{
				dw->handle.window = (MCSysWindowHandle)GetFocus();
				MCdispatcher->wkfocus(dw);
			}
			curinfo->handled = True;
		}
		else
		{
			MCEventnode *tptr = new MCEventnode(hwnd, msg, wParam, lParam, 0,
			                                    MCmodifierstate, MCeventtime);
			pms->appendevent(tptr);
		}
		break;
	case WM_KILLFOCUS: //FocusOut:
		if (curinfo->dispatch)
		{
			if (MCtracewindow == DNULL || hwnd != (HWND)MCtracewindow->handle.window)
				MCdispatcher->wkunfocus(dw);
			curinfo->handled = True;
		}
		else
		{
			MCEventnode *tptr = new MCEventnode(hwnd, msg, wParam, lParam, 0,
			                                    MCmodifierstate, MCeventtime);
			pms->appendevent(tptr);
		}
		break;

	case WM_SYSKEYDOWN:
	case WM_SYSCHAR:
	case WM_CHAR:
	case WM_KEYDOWN:
	{
		if (wParam == VK_CONTROL)
			break;

		char t_input_char;
		t_input_char = (char)wParam;

		if (IsWindowUnicode(hwnd))
		{
			if (wParam >= 128)
			{
				bool t_is_unicode;
				WCHAR t_wide[1];
			
				// MW-2012-07-25: [[ Bug 9200 ]] Make sure we roundtrip the input character
				//   through 1252 *not* the active code page (which could be anything).
				t_wide[0] = (WCHAR)wParam;
				t_is_unicode = (WideCharToMultiByte(1252, 0, t_wide, 1, &t_input_char, 1, NULL, NULL) == 0);
				if (!t_is_unicode)
				{
					WCHAR t_reverse_wide[1];
					t_is_unicode = MultiByteToWideChar(1252, 0, &t_input_char, 1, t_reverse_wide, 1) == 0;
					if (!t_is_unicode)
						t_is_unicode = t_reverse_wide[0] != t_wide[0];
				}

				if (t_is_unicode && (msg == WM_CHAR || msg == WM_SYSCHAR))
				{
					if (MCactivefield)
					{
						MCString t_unicode_string;
						t_unicode_string . set((char *)t_wide, 2);

						// MW-2012-02-03: [[ Unicode Block ]] Use the new finsert method to insert
						//   text in unicode mode.
						MCactivefield -> finsertnew(FT_IMEINSERT, t_unicode_string, LCH_UNICODE, true);
					}
					break;
				}
			}
		}
		else if (wParam >= 128 && (((MCScreenDC *)MCscreen) -> system_codepage) != (((MCScreenDC *)MCscreen) -> input_codepage))
		{
			WCHAR t_unicode_char;
			MultiByteToWideChar((((MCScreenDC *)MCscreen) -> input_codepage), 0, &t_input_char, 1, &t_unicode_char, 1);

			bool t_is_unicode;
			t_is_unicode = (WideCharToMultiByte((((MCScreenDC *)MCscreen) -> system_codepage), 0, &t_unicode_char, 1, &t_input_char, 1, NULL, NULL) == 0);
			if (!t_is_unicode)
			{
				WCHAR t_reverse_unicode_char;
				t_is_unicode = MultiByteToWideChar((((MCScreenDC *)MCscreen) -> system_codepage), 0, &t_input_char, 1, &t_reverse_unicode_char, 1) == 0;
				if (!t_is_unicode)
					t_is_unicode = t_reverse_unicode_char != t_unicode_char;
			}

			if (t_is_unicode)
			{
				if (MCactivefield)
				{
					MCString t_unicode_string;
					t_unicode_string . set((char *)&t_unicode_char, 2);

					// MW-2012-02-03: [[ Unicode Block ]] Use the new finsert method to insert
					//   text in unicode mode.
					MCactivefield -> finsertnew(FT_IMEINSERT, t_unicode_string, LCH_UNICODE, true);
				}
				break;
			}
		}

		if (msg == WM_CHAR || msg == WM_SYSCHAR)
			wParam = t_input_char;

		buffer[0] = buffer[1] = 0;

		if (msg == WM_CHAR || msg == WM_SYSCHAR)
			buffer[0] = lastchar = wParam;

		// MW-2010-11-17: [[ Bug 3892 ]] Ctrl+Alt can be the same as AltGr.
		//   If we are a CHAR message *and* have a non-control character *and* have Ctrl+Alt set, we discard the modifiers
		if ((msg == WM_CHAR || msg == WM_SYSCHAR) && wParam >= 32 && (MCmodifierstate & (MS_CONTROL | MS_ALT)) == (MS_CONTROL | MS_ALT))
			MCmodifierstate = 0;

		if (curinfo->keysym == 0) // event came from some other dispatch
			keysym = pms->getkeysym(wParam, lParam);
		else
			keysym = curinfo->keysym;
		lastkeysym = keysym;
		if (MCmodifierstate & MS_CONTROL)
			if (wParam == VK_CANCEL || keysym == '.')
			{
				if (MCallowinterrupts && !MCdefaultstackptr->cantabort())
					curinfo->abort = True;
				else
					MCinterrupt = True;
			}
			else
				if (msg == WM_KEYDOWN)
					buffer[0] = lastchar = wParam;
		if (curinfo->dispatch)
		{
			if (MCtracewindow == DNULL || hwnd != (HWND)MCtracewindow->handle.window)
			{
				uint2 count = LOWORD(lParam);
				while (count--)
				{
					if (!MCdispatcher->wkdown(dw, buffer, keysym)
					        && (msg == WM_SYSKEYDOWN || msg == WM_SYSCHAR))
						return IsWindowUnicode(hwnd) ? DefWindowProcW(hwnd, msg, wParam, lParam) : DefWindowProcA(hwnd, msg, wParam, lParam);
					if (count || lParam & 0x40000000)
						MCdispatcher->wkup(dw, buffer, keysym);
				}
				curinfo->handled = curinfo->reset = True;
			}
		}
		else
		{
			MCEventnode *tptr = new MCEventnode(hwnd, msg, wParam, lParam, keysym,
			                                    MCmodifierstate, MCeventtime);
			pms->appendevent(tptr);
		}
	}
	break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
	{	
		if (curinfo->keysym == 0) // event came from some other dispatch
			keysym = pms->getkeysym(wParam, lParam);
		else
			keysym = curinfo->keysym;
		if (keysym == lastkeysym)
			buffer[0] = lastchar;
		else
			buffer[0] = 0;
		buffer[1] = 0;
		if (curinfo->dispatch)
		{
			if (MCtracewindow == DNULL || hwnd != (HWND)MCtracewindow->handle.window)
			{
				MCeventtime = GetMessageTime(); //krevent->time;
				MCdispatcher->wkup(dw, buffer, keysym);
				curinfo->handled = curinfo->reset = True;
			}
		}
		else
		{
			MCEventnode *tptr = new MCEventnode(hwnd, msg, wParam, lParam, 0,
			                                    MCmodifierstate, MCeventtime);
			pms->appendevent(tptr);
		}
	}	
	break;
	case WM_IME_STARTCOMPOSITION:
		if (!MCinlineinput)
			return IsWindowUnicode(hwnd) ? DefWindowProcW(hwnd, msg, wParam, lParam) : DefWindowProcA(hwnd, msg, wParam, lParam);
		break;
	case WM_IME_ENDCOMPOSITION:
		if (!MCinlineinput)
			return IsWindowUnicode(hwnd) ? DefWindowProcW(hwnd, msg, wParam, lParam) : DefWindowProcA(hwnd, msg, wParam, lParam);
		break;
	case WM_IME_CHAR:
		{
			if (!MCactivefield)
				break;
			uint2 unicodekey = MAXUINT2;
			uint4 destlen;
			if (IsWindowUnicode(hwnd))
			{
				unicodekey = wParam;
				destlen = 2;
			}
			else
			{
				char multibytechar[3];
				multibytechar[0] =  HIBYTE((WORD)wParam) ;
				multibytechar[1] =  LOBYTE((WORD)wParam) ;
				multibytechar[2] = '\0';
				MCU_multibytetounicode(multibytechar, 2, (char *)&unicodekey, 2,
					                     destlen,  MCS_langidtocharset(LOWORD(GetKeyboardLayout(0))));
			}
			MCString unicodestr;
			unicodestr.set((char *)&unicodekey, destlen);

			// MW-2012-02-03: [[ Unicode Block ]] Use the new finsert method to insert
			//   text in unicode mode.
			MCactivefield->finsertnew(FT_IMEINSERT, unicodestr, 0, true);
		}
		break;
	case WM_IME_COMPOSITION:
		{
			if (!MCinlineinput)
				return IsWindowUnicode(hwnd) ? DefWindowProcW(hwnd, msg, wParam, lParam) : DefWindowProcA(hwnd, msg, wParam, lParam);
			if (!MCactivefield)
				break;
			DWORD dwindex = 0;
			if (lParam & GCS_RESULTSTR)
			{
				MCactivefield->stopcomposition(True,False);
				dwindex = GCS_RESULTSTR;
			}
			else if (lParam & GCS_COMPSTR)
			{
				MCactivefield->startcomposition();
				dwindex = GCS_COMPSTR;
			}
			HIMC hIMC = ImmGetContext(hwnd);
			if (!hIMC || !dwindex)
				break;
			int2 cursorpos = LOWORD(ImmGetCompositionStringA(hIMC, GCS_CURSORPOS,
			                        NULL, 0));
			MCactivefield->setcompositioncursoroffset(cursorpos << 1);
			uint2 compstrsize = 0;
			char *compstring = NULL;
			compstrsize = (uint2)ImmGetCompositionStringW(hIMC, dwindex, NULL, 0);
			compstring = new char[compstrsize+sizeof(WCHAR)];
			ImmGetCompositionStringW(hIMC, dwindex, compstring, compstrsize);
			MCString unicodestr(compstring, compstrsize);

			// MW-2012-02-03: [[ Unicode Block ]] Use the new finsert method to insert
			//   text in unicode mode.
			MCactivefield->finsertnew(FT_IMEINSERT, unicodestr, 0, true);
			delete compstring;
			ImmReleaseContext(hwnd, hIMC);
		}
		break;
	case WM_IME_NOTIFY: //sent when IME opens windows
		switch (wParam)
		{
		case  IMN_OPENCANDIDATE:
			{
				HIMC hIMC = ImmGetContext(hwnd);
				DWORD imeprop = ImmGetProperty(GetKeyboardLayout(0), IGP_PROPERTY);
				if (imeprop & IME_PROP_AT_CARET)
				{
					if (MCactivefield)
					{
						uint1 i;
						for (i = 0; i < 4; i++)
						{
							MCRectangle r;
							CANDIDATEFORM cdf;
							cdf.dwIndex = i;
							cdf.dwStyle = CFS_CANDIDATEPOS;
							MCactivefield->getcompositionrect(r, -1);
							cdf.ptCurrentPos.x = r.x;
							cdf.ptCurrentPos.y = r.y + r.height + 32;
							cdf.rcArea.right = 1;
							cdf.rcArea.left = r.x;
							cdf.rcArea.top = r.y + r.height + 32;
							cdf.rcArea.bottom = 1;
							ImmSetCandidateWindow(hIMC, &cdf);
						}
					}
				}
			}
			break;
		case IMN_SETOPENSTATUS:
			{
				COMPOSITIONFORM cpf;
				HIMC hIMC = ImmGetContext(hwnd);
				cpf.dwStyle = CFS_DEFAULT;
				cpf.ptCurrentPos.x = 0;
				cpf.ptCurrentPos.y = 0;
				ImmSetCompositionWindow(hIMC, &cpf);
				ImmReleaseContext(hwnd, hIMC);
			}
			break;
		}
		return IsWindowUnicode(hwnd) ? DefWindowProcW(hwnd, msg, wParam, lParam) : DefWindowProcA(hwnd, msg, wParam, lParam);
		break;
	case WM_SETCURSOR:
		if (curinfo->live && !pms->isgrabbed() && LOWORD(lParam) != HTCLIENT)
			return IsWindowUnicode(hwnd) ? DefWindowProcW(hwnd, msg, wParam, lParam) : DefWindowProcA(hwnd, msg, wParam, lParam);
		MCmousestackptr = MCdispatcher->findstackd(dw);
		if (MCmousestackptr != NULL)
		{
			MCmousestackptr->resetcursor(True);
			if (pms->getmousetimer() == 0)
				pms->setmousetimer(timeSetEvent(LEAVE_CHECK_INTERVAL, 100,
				                                mouseproc, 0, TIME_ONESHOT));
		}
		if (omousestack != MCmousestackptr)
		{
			if (omousestack != NULL && omousestack != MCtracestackptr)
				omousestack->munfocus();
			if (MCmousestackptr != NULL && MCmousestackptr != MCtracestackptr)
				MCmousestackptr->enter();
		}
		break;
	case WM_CAPTURECHANGED:
		if (curinfo->live)
		{
			if (pms->isgrabbed())
			{
				MCStack *sptr = MCdispatcher->findstackd(dw);
				if (sptr != NULL)
				{
					if (lastdown != 0)
						sptr->mup(lastdown);
					buffer[0] = 0x1B; // escape
					buffer[1] = '\0';
					Boolean oldlock = MClockmessages;
					MClockmessages = True;
					sptr->kdown(buffer, XK_Escape);
					sptr->kup(buffer, XK_Escape);
					MClockmessages = oldlock;
					sptr->munfocus();
					pms->setgrabbed(False);
					curinfo->handled = True;
				}
				capturehwnd = NULL;
			}
		}
		break;
	case WM_MOUSEMOVE:  //MotionNotify:
	case WM_NCMOUSEMOVE:
		// IM-2013-09-23: [[ FullscreenMode ]] Update mouseloc with MCscreen getters & setters
		MCStack *t_old_mousestack;
		MCPoint t_old_mouseloc;
		MCscreen->getmouseloc(t_old_mousestack, t_old_mouseloc);
		if (t_old_mouseloc.x != t_mouseloc.x || t_old_mouseloc.y != t_mouseloc.y)
		{
			MCscreen->setmouseloc(t_old_mousestack, t_mouseloc);
			if (curinfo->dispatch)
			{
				if (msg != WM_NCMOUSEMOVE)
					MCscreen->setmouseloc(MCdispatcher->findstackd(dw), t_mouseloc);
				if (MCtracewindow == DNULL || hwnd != (HWND)MCtracewindow->handle.window)
				{
					if (t_old_mousestack != NULL && MCmousestackptr != t_old_mousestack)
						t_old_mousestack->munfocus();
					if (msg == WM_MOUSEMOVE)
					{
						MCPoint t_clickloc;
						MCStack *t_stackptr;
						MCscreen->getclickloc(t_stackptr, t_clickloc);

						MCdispatcher->wmfocus(dw, t_mouseloc.x, t_mouseloc.y);
						if (capturehwnd != NULL && MCbuttonstate != 0 && !dragclick && (MCU_abs(t_mouseloc.x - t_clickloc.x) >= MCdragdelta || MCU_abs(t_mouseloc.y - t_clickloc.y) >= MCdragdelta))
						{
							dragclick = True;
							MCdispatcher -> wmdrag(dw);
						}
					}
					else
						if (MCmousestackptr != NULL)
							MCmousestackptr->munfocus();
					curinfo->handled = True;
				}
			}
			else
			{
				MCEventnode *tptr = new MCEventnode(hwnd, msg, wParam, lParam, 0,
				                                    MCmodifierstate, MCeventtime);
				pms->appendevent(tptr);
			}
		}
		if (msg == WM_NCMOUSEMOVE)
			return IsWindowUnicode(hwnd) ? DefWindowProcW(hwnd, msg, wParam, lParam) : DefWindowProcA(hwnd, msg, wParam, lParam);
		break;
	case WM_APP:
		if (MCmousestackptr != NULL && MCdispatcher->getmenu() == NULL)
		{
			POINT p;
			if (!GetCursorPos(&p)
			        || !MCU_point_in_rect(MCmousestackptr->getrect(),
			                              (int2)p.x, (int2)p.y))
			{
				if (MCmousestackptr != MCtracestackptr)
					MCmousestackptr->munfocus();
			}
			else
				pms->setmousetimer(timeSetEvent(LEAVE_CHECK_INTERVAL, 100,
				                                mouseproc, 0, TIME_ONESHOT));
		}
		curinfo->handled = True;
		break;
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
		if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP
		        || msg == WM_LBUTTONDBLCLK)
			button = 1;
		else
			if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP
			        || msg == WM_MBUTTONDBLCLK)
				button = 2;
			else
				button = 3;
		if (msg == WM_LBUTTONUP || msg == WM_MBUTTONUP || msg == WM_RBUTTONUP)
		{
			if (curinfo->live && !pms->isgrabbed())
			{
				ReleaseCapture();
				capturehwnd = NULL;
			}
			MCbuttonstate &= ~(1L << (button - 1));
			down = False;
			lastdown = 0;
		}
		else
		{
			if (curinfo->live && !pms->isgrabbed())
			{
				SetCapture(hwnd);
				capturehwnd = hwnd;
				lastdown = button;
			}
			MCbuttonstate |= 1L << (button - 1);
			down = True;
			if (msg == WM_LBUTTONDBLCLK || msg == WM_MBUTTONDBLCLK
			        || msg == WM_RBUTTONDBLCLK)
				doubledown = True;
		}
		if (curinfo->dispatch)
		{
			if (MCtracewindow == DNULL || hwnd != (HWND)MCtracewindow->handle.window)
				if (down)
					if (doubledown)
						MCdispatcher->wdoubledown(dw, button);
					else
					{
						if (doubleclick && MCeventtime - clicktime < MCdoubletime
						        && MCU_abs(MCclicklocx - t_mouseloc.x) < MCdoubledelta
						        && MCU_abs(MCclicklocy - t_mouseloc.y) < MCdoubledelta)
							tripleclick = True;
						else
							tripleclick = False;
						doubleclick = False;
						// IM-2013-09-23: [[ FullscreenMode ]] Update clickloc with MCscreen getters & setters
						MCscreen->setclickloc(MCmousestackptr, t_mouseloc);
						dragclick = False;
						MCdispatcher->wmfocus(dw, t_mouseloc.x, t_mouseloc.y);
						MCdispatcher->wmdown(dw, button);
					}
				else
				{
					if (doubledown)
					{
						doubledown = False;
						doubleclick = True;
						clicktime = MCeventtime;
						MCdispatcher->wdoubleup(dw, button);
					}
					else
						MCdispatcher->wmup(dw, button);
				}
			curinfo->handled = curinfo->reset = True;
		}
		else
		{
			MCEventnode *tptr = new MCEventnode(hwnd, msg, wParam, lParam, 0,
			                                    MCmodifierstate, MCeventtime);
			pms->appendevent(tptr);
		}
		break;
	case WM_SIZE:
		{
			MCStack *target = MCdispatcher->findstackd(dw);
			if (target != NULL)
			{
				if (wParam == SIZE_MINIMIZED)
					target->iconify();
				else
					if (target->isiconic())
					{
						MCstacks->restack(target);
						target->view_configure(true);
						target->uniconify();
						SetWindowPos((HWND)target -> getwindow() -> handle . window, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
					}
					else
						target->view_configure(true);
				curinfo->handled = True;
			}
		}
		break;
	case WM_MOVE:
		MCdispatcher->configure(dw);
		curinfo->handled = True;
		break;
	case WM_CLOSE:
		MCdispatcher->wclose(dw);
		curinfo->handled = True;
		break;
	case WM_GETMINMAXINFO:
		target = MCdispatcher->findstackd(dw);
		if (target != NULL)
			target->constrain(lParam);
		break;
	case WM_ERASEBKGND:
		break;
	case WM_TIMER:
		curinfo->handled = True;
		if (MCmousestackptr != NULL && MCdispatcher->getmenu() == NULL)
		{
			int2 x, y;
			pms->querymouse(x, y);
			MCRectangle rect;
			if (pms->getwindowgeometry(MCmousestackptr->getw(), rect)
			        && capturehwnd == NULL && !pms->getgrabbed()
			        && !MCU_point_in_rect(rect, x, y))
			{
				MCmousestackptr->munfocus();
				MCmousestackptr = NULL;
			}
		}
		break;
	case WM_CANCELMODE:
		if (pms->isgrabbed())
		{
			buffer[0] = 0x1B;
			buffer[1] = '\0';
			Boolean oldlock = MClockmessages;
			MClockmessages = True;
			MCdispatcher->wkdown(dw, buffer, XK_Escape);
			MCdispatcher->wkup(dw, buffer, XK_Escape);
			MClockmessages = oldlock;
			curinfo->handled = True;
			pms->setgrabbed(False);
			MCmousex = MCmousey = -1; // prevent button msg from reopening menu
			MCdispatcher->wmfocus(dw, MCmousex, MCmousey);
		}
		break;
	case MM_MCINOTIFY:
		if (wParam == MCI_NOTIFY_SUCCESSFUL)
		{
			MCPlayer *tptr = MCplayers;
			while (tptr != NULL)
			{
				if (lParam == (LPARAM)tptr->getDeviceID())
				{
					if (tptr->isdisposable())
						tptr->playstop();
					else
						tptr->message_with_args(MCM_play_stopped, tptr->getname());
					break;
				}
				tptr = tptr->getnextplayer();
			}
			curinfo->handled = True;
		}
		break;
	case WM_USER:
		{
			uint2 i;
			for (i = 0 ; i < MCnsockets ; i++)
			{
				if (MCsockets[i]->fd == 0)
					MCsockets[i]->readsome();
				if (wParam == MCsockets[i]->fd && !MCsockets[i]->shared)
					break;
			}
			if (i < MCnsockets)
			{
				if (WSAGETSELECTERROR(lParam))
				{
					MCsockets[i]->error = new char[16 + I4L];
					sprintf(MCsockets[i]->error, "Error %d on socket",
					        WSAGETSELECTERROR(lParam));
					MCsockets[i]->doclose();
				}
				else
				{
					/* I.M
					 * TODO - look in to this further:
					 * we sometimes get FD_READ, but there's no data ready to read
					 * so trying to read when using SSL results in us getting stuck
					 * in SSTATE_RETRYREAD, which won't be cleared until data is
					 * available to read.  As a quick fix, we can check the socket with select()
					 */
					int t_events = 0;
					TIMEVAL t_time = {0,0};
					fd_set rmaskfd, wmaskfd, emaskfd;
					FD_ZERO(&rmaskfd);
					FD_ZERO(&wmaskfd);
					FD_ZERO(&emaskfd);
					FD_SET(wParam, &rmaskfd);
					FD_SET(wParam, &emaskfd);
					select(0, &rmaskfd, &wmaskfd, &emaskfd, &t_time);
					if (FD_ISSET(wParam, &emaskfd))
						t_events = t_events;
					if (FD_ISSET(wParam, &rmaskfd))
						t_events |= FD_READ;
					if (FD_ISSET(wParam, &wmaskfd))
						t_events |= FD_WRITE;
					switch (WSAGETSELECTEVENT(lParam))
					{
					case FD_OOB: // bogus, from MCS_read_socket
					case FD_READ:
						if (t_events & FD_READ)
							MCsockets[i]->readsome();
						break;
					case FD_WRITE:
						MCsockets[i]->writesome();
						MCsockets[i]->setselect();
						break;
					case FD_CONNECT:
						MCsockets[i]->writesome();
						MCsockets[i]->readsome();
						MCsockets[i]->setselect();
						break;
					case FD_ACCEPT:
						MCsockets[i]->acceptone();
						break;
					case FD_CLOSE:
						MCsockets[i]->readsome();
#ifdef MCSSL

						if (MCsockets[i]->fd != 0 && !MCsockets[i]->secure)
#else

						if (MCsockets[i]->fd != 0)
#endif

							MCsockets[i]->doclose();
						break;
					}
				}
			}
			curinfo->handled = True;
			break;
		}
	case WM_WINDOWPOSCHANGING:
	{
		((MCScreenDC *)MCscreen) -> restackwindows(hwnd, msg, wParam, lParam);
//			return IsWindowUnicode(hwnd) ? DefWindowProcW(hwnd, msg, wParam, lParam) : DefWindowProcA(hwnd, msg, wParam, lParam);
	}
	break;
	case WM_POWERBROADCAST:
		MCS_reset_time();
		return TRUE;
	case WM_THEMECHANGED:
	case WM_SYSCOLORCHANGE:
		if (hwnd == pms->getinvisiblewindow() && MCcurtheme && MCcurtheme->getthemeid() == LF_NATIVEWIN)
		{
			MCcurtheme->unload();
			MCcurtheme->load();

			// MW-2011-08-17: [[ Redraw ]] The theme has changed so redraw everything.
			MCRedrawDirtyScreen();
		}
		break;
	case WM_ACTIVATEAPP:
		if (wParam != isactive)
		{
			MCstacks->hidepalettes(!wParam);
			((MCScreenDC *)MCscreen) -> hidebackdrop(!wParam);
			if (MCdefaultstackptr != NULL)
				MCdefaultstackptr->getcard()->message(wParam ? MCM_resume : MCM_suspend);
			isactive = wParam;
			if (!wParam)
			{
				if (pms->taskbarhidden)
				{ //we are suspended, show menu bar for other process
					pms->showtaskbar();
					pms->taskbarhidden = True;
				}
			}
			else
			{
				if (pms->taskbarhidden)
				{
					pms->taskbarhidden = False;
					pms->hidetaskbar();
				}
			}
		}
		break;
	case WM_INPUTLANGCHANGE:
		{
			LCID t_locale_id;
			t_locale_id = MAKELCID(lParam, SORT_DEFAULT);
			
			char t_info[8];
			GetLocaleInfoA(t_locale_id, LOCALE_IDEFAULTANSICODEPAGE, t_info, 8);
			((MCScreenDC *)MCscreen) -> input_codepage = atoi(t_info);
			((MCScreenDC *)MCscreen) -> system_codepage = GetACP();
		}
		break;

	case WM_NCACTIVATE:
		if (MCactivatepalettes && wParam == FALSE && MCstacks->getactive())
		{
			MCStack *sptr = MCdispatcher->findstackd(dw);
			if (sptr != NULL && sptr->getmode() == WM_PALETTE)
				wParam = TRUE;
		}
		return IsWindowUnicode(hwnd) ? DefWindowProcW(hwnd, msg, wParam, lParam) : DefWindowProcA(hwnd, msg, wParam, lParam);
	case WM_MOUSEWHEEL:
	case WM_MOUSEHWHEEL:
		if (MCmousestackptr != NULL)
		{
			MCObject *mfocused = MCmousestackptr->getcard()->getmfocused();
			if (mfocused == NULL)
				mfocused = MCmousestackptr -> getcard();

			if (mfocused != NULL)
			{
				int4 val = (short)HIWORD(wParam);
				if (msg == WM_MOUSEWHEEL)
				{
					if (val < 0)
						mfocused->kdown("", XK_WheelUp);
					else
						mfocused->kdown("", XK_WheelDown);
				}
				else if (msg == WM_MOUSEHWHEEL)
				{
					if (val < 0)
						mfocused->kdown("", XK_WheelLeft);
					else
						mfocused->kdown("", XK_WheelRight);
				}
			}
		}
	break;
	default:
		return IsWindowUnicode(hwnd) ? DefWindowProcW(hwnd, msg, wParam, lParam) : DefWindowProcA(hwnd, msg, wParam, lParam);
	}

	return 0;
}