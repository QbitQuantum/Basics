LRESULT CALLBACK wf_ll_kbd_proc(int nCode, WPARAM wParam, LPARAM lParam)
{
	wfInfo* wfi;
	DWORD rdp_scancode;
	rdpInput* input;
	PKBDLLHOOKSTRUCT p;

	DEBUG_KBD("Low-level keyboard hook, hWnd %X nCode %X wParam %X", g_focus_hWnd, nCode, wParam);

	if (g_focus_hWnd && (nCode == HC_ACTION))
	{
		switch (wParam)
		{
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYUP:
				wfi = (wfInfo*) GetWindowLongPtr(g_focus_hWnd, GWLP_USERDATA);
				p = (PKBDLLHOOKSTRUCT) lParam;

				if (!wfi || !p)
					return 1;
				
				input = wfi->instance->input;
				rdp_scancode = MAKE_RDP_SCANCODE((BYTE) p->scanCode, p->flags & LLKHF_EXTENDED);

				DEBUG_KBD("keydown %d scanCode %04X flags %02X vkCode %02X",
					(wParam == WM_KEYDOWN), (BYTE) p->scanCode, p->flags, p->vkCode);

				if (wfi->fs_toggle &&
					((p->vkCode == VK_RETURN) || (p->vkCode == VK_CANCEL)) &&
					(GetAsyncKeyState(VK_CONTROL) & 0x8000) &&
					(GetAsyncKeyState(VK_MENU) & 0x8000)) /* could also use flags & LLKHF_ALTDOWN */
				{
					if (wParam == WM_KEYDOWN)
					{
						wf_toggle_fullscreen(wfi);
						return 1;
					}
				}

				if (rdp_scancode == RDP_SCANCODE_NUMLOCK_EXTENDED)
				{
					/* Windows sends NumLock as extended - rdp doesn't */
					DEBUG_KBD("hack: NumLock (x45) should not be extended");
					rdp_scancode = RDP_SCANCODE_NUMLOCK;
				}
				else if (rdp_scancode == RDP_SCANCODE_NUMLOCK)
				{
					/* Windows sends Pause as if it was a RDP NumLock (handled above).
					 * It must however be sent as a one-shot Ctrl+NumLock */
					if (wParam == WM_KEYDOWN)
					{
						DEBUG_KBD("Pause, sent as Ctrl+NumLock");
						freerdp_input_send_keyboard_event_ex(input, TRUE, RDP_SCANCODE_LCONTROL);
						freerdp_input_send_keyboard_event_ex(input, TRUE, RDP_SCANCODE_NUMLOCK);
						freerdp_input_send_keyboard_event_ex(input, FALSE, RDP_SCANCODE_LCONTROL);
						freerdp_input_send_keyboard_event_ex(input, FALSE, RDP_SCANCODE_NUMLOCK);
					}
					else
					{
						DEBUG_KBD("Pause up");
					}

					return 1;
				}
				else if (rdp_scancode == RDP_SCANCODE_RSHIFT_EXTENDED)
				{
					DEBUG_KBD("right shift (x36) should not be extended");
					rdp_scancode = RDP_SCANCODE_RSHIFT;
				}

				freerdp_input_send_keyboard_event_ex(input, !(p->flags & LLKHF_UP), rdp_scancode);

				if (p->vkCode == VK_CAPITAL)
					DEBUG_KBD("caps lock is processed on client side too to toggle caps lock indicator");
				else
					return 1;

				break;
		}
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}