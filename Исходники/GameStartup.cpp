PLUGIN_SDK_WINPROC_INJECTOR(LRESULT CALLBACK CGameStartup::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam))
{
	switch(msg)
	{
	case WM_CLOSE:
		if (gEnv && gEnv->pSystem)
			gEnv->pSystem->Quit();
		return 0;
	case WM_MOUSEACTIVATE:
		if (g_debugWindowsMessages && gEnv && gEnv->pLog)
			gEnv->pLog->Log("MSG: WM_MOUSEACTIVATE (%s %s)", (GetFocus()==hWnd)?"focused":"", (GetForegroundWindow()==hWnd)?"foreground":"");
		return MA_ACTIVATEANDEAT;
	case WM_ENTERSIZEMOVE:
		if (g_debugWindowsMessages && gEnv && gEnv->pLog)
			gEnv->pLog->Log("MSG: WM_ENTERSIZEMOVE (%s %s)", (GetFocus()==hWnd)?"focused":"", (GetForegroundWindow()==hWnd)?"foreground":"");
		if (gEnv && gEnv->pSystem && gEnv->pSystem->GetIHardwareMouse())
		{
			gEnv->pSystem->GetIHardwareMouse()->IncrementCounter();
		}
		return  0;
	case WM_EXITSIZEMOVE:
		if (g_debugWindowsMessages && gEnv && gEnv->pLog)
			gEnv->pLog->Log("MSG: WM_EXITSIZEMOVE (%s %s)", (GetFocus()==hWnd)?"focused":"", (GetForegroundWindow()==hWnd)?"foreground":"");
		if (gEnv && gEnv->pSystem && gEnv->pSystem->GetIHardwareMouse())
		{
			gEnv->pSystem->GetIHardwareMouse()->DecrementCounter();
		}
		return  0;
	case WM_ENTERMENULOOP:
		if (g_debugWindowsMessages && gEnv && gEnv->pLog)
			gEnv->pLog->Log("MSG: WM_ENTERMENULOOP (%s %s)", (GetFocus()==hWnd)?"focused":"", (GetForegroundWindow()==hWnd)?"foreground":"");
		if (gEnv && gEnv->pSystem && gEnv->pSystem->GetIHardwareMouse())
		{
			gEnv->pSystem->GetIHardwareMouse()->IncrementCounter();
		}
		return  0;
	case WM_EXITMENULOOP:
		if (g_debugWindowsMessages && gEnv && gEnv->pLog)
			gEnv->pLog->Log("MSG: WM_EXITMENULOOP (%s %s)", (GetFocus()==hWnd)?"focused":"", (GetForegroundWindow()==hWnd)?"foreground":"");
		if (gEnv && gEnv->pSystem && gEnv->pSystem->GetIHardwareMouse())
		{
			gEnv->pSystem->GetIHardwareMouse()->DecrementCounter();
		}
		return  0;
	case WM_HOTKEY:
	case WM_SYSCHAR:	// prevent ALT + key combinations from creating 'ding' sounds
		return  0;
	case WM_CHAR:
		{
			if (gEnv && gEnv->pInput)
			{
				SInputEvent event;
				event.modifiers = gEnv->pInput->GetModifiers();
				event.deviceId = eDI_Keyboard;
				event.state = eIS_UI;
				event.value = 1.0f;
				event.pSymbol = 0;//m_rawKeyboard->GetSymbol((lParam>>16)&0xff);
				if (event.pSymbol)
					event.keyId = event.pSymbol->keyId;

				event.inputChar = (wchar_t)wParam;
				gEnv->pInput->PostInputEvent(event);
			}
		}
		break;
	case WM_SYSKEYDOWN:	// prevent ALT-key entering menu loop
			if (wParam != VK_RETURN && wParam != VK_F4)
			{
				return 0;
			}
			else
			{
				if (wParam == VK_RETURN)	// toggle fullscreen
				{
					if (gEnv && gEnv->pRenderer && gEnv->pRenderer->GetRenderType() != eRT_DX11)
					{
						ICVar *pVar = gEnv->pConsole->GetCVar("r_Fullscreen");
						if (pVar)
						{
							int fullscreen = pVar->GetIVal();
							pVar->Set((int)(fullscreen == 0));
						}
					}
				}
				// let the F4 pass through to default handler (it will send an WM_CLOSE)
			}
		break;
	case WM_SETCURSOR:
		if(g_pGame)
		{
			HCURSOR hCursor = LoadCursor(GetModuleHandle(0),MAKEINTRESOURCE(DEFAULT_CURSOR_RESOURCE_ID));
			::SetCursor(hCursor);
		}
		return 0;
	case WM_MOUSEMOVE:
		if(gEnv && gEnv->pHardwareMouse)
		{
			gEnv->pHardwareMouse->Event(LOWORD(lParam),HIWORD(lParam),HARDWAREMOUSEEVENT_MOVE);
		}
		return 0;
	case WM_LBUTTONDOWN:
		if(gEnv && gEnv->pHardwareMouse)
		{
			gEnv->pHardwareMouse->Event(LOWORD(lParam),HIWORD(lParam),HARDWAREMOUSEEVENT_LBUTTONDOWN);
		}
		return 0;
	case WM_LBUTTONUP:
		if(gEnv && gEnv->pHardwareMouse)
		{
			gEnv->pHardwareMouse->Event(LOWORD(lParam),HIWORD(lParam),HARDWAREMOUSEEVENT_LBUTTONUP);
		}
		return 0;
	case WM_LBUTTONDBLCLK:
		if(gEnv && gEnv->pHardwareMouse)
		{
			gEnv->pHardwareMouse->Event(LOWORD(lParam),HIWORD(lParam),HARDWAREMOUSEEVENT_LBUTTONDOUBLECLICK);
		}
		return 0;
	case WM_MOVE:
		if (g_debugWindowsMessages && gEnv && gEnv->pLog)
			gEnv->pLog->Log("MSG: WM_MOVE %d %d (%s %s)", LOWORD(lParam), HIWORD(lParam), (GetFocus()==hWnd)?"focused":"", (GetForegroundWindow()==hWnd)?"foreground":"");
		if(gEnv && gEnv->pSystem && gEnv->pSystem->GetISystemEventDispatcher())
		{
			gEnv->pSystem->GetISystemEventDispatcher()->OnSystemEvent(ESYSTEM_EVENT_MOVE,LOWORD(lParam), HIWORD(lParam));
		}
    return DefWindowProc(hWnd, msg, wParam, lParam);
	case WM_SIZE:
		if (g_debugWindowsMessages && gEnv && gEnv->pLog)
			gEnv->pLog->Log("MSG: WM_SIZE %d %d (%s %s)", LOWORD(lParam), HIWORD(lParam), (GetFocus()==hWnd)?"focused":"", (GetForegroundWindow()==hWnd)?"foreground":"");
		if(gEnv && gEnv->pSystem && gEnv->pSystem->GetISystemEventDispatcher())
		{
			gEnv->pSystem->GetISystemEventDispatcher()->OnSystemEvent(ESYSTEM_EVENT_RESIZE,LOWORD(lParam), HIWORD(lParam));
		}
    return DefWindowProc(hWnd, msg, wParam, lParam);
	case WM_ACTIVATE:
		if (g_debugWindowsMessages && gEnv && gEnv->pLog)
			gEnv->pLog->Log("MSG: WM_ACTIVATE %d (%s %s)", LOWORD(wParam), (GetFocus()==hWnd)?"focused":"", (GetForegroundWindow()==hWnd)?"foreground":"");

		if(gEnv && gEnv->pSystem && gEnv->pSystem->GetISystemEventDispatcher())
		{
			gEnv->pSystem->GetISystemEventDispatcher()->OnSystemEvent(ESYSTEM_EVENT_ACTIVATE, LOWORD(wParam) != WA_INACTIVE, HIWORD(wParam));
		}
		break;
	case WM_SETFOCUS:
		if (g_debugWindowsMessages && gEnv && gEnv->pLog)
			gEnv->pLog->Log("MSG: WM_SETFOCUS (%s %s)", (GetFocus()==hWnd)?"focused":"", (GetForegroundWindow()==hWnd)?"foreground":"");
		if(gEnv && gEnv->pSystem && gEnv->pSystem->GetISystemEventDispatcher())
		{
			gEnv->pSystem->GetISystemEventDispatcher()->OnSystemEvent(ESYSTEM_EVENT_CHANGE_FOCUS, 1, 0);
		}
		break;
	case WM_KILLFOCUS:
		if (g_debugWindowsMessages && gEnv && gEnv->pLog)
			gEnv->pLog->Log("MSG: WM_KILLFOCUS (%s %s)", (GetFocus()==hWnd)?"focused":"", (GetForegroundWindow()==hWnd)?"foreground":"");
		if(gEnv && gEnv->pSystem && gEnv->pSystem->GetISystemEventDispatcher())
		{
			gEnv->pSystem->GetISystemEventDispatcher()->OnSystemEvent(ESYSTEM_EVENT_CHANGE_FOCUS, 0, 0);
		}
		break;
  case WM_WINDOWPOSCHANGED:
		if (g_debugWindowsMessages && gEnv && gEnv->pLog)
			gEnv->pLog->Log("MSG: WM_WINDOWPOSCHANGED (%s %s)", (GetFocus()==hWnd)?"focused":"", (GetForegroundWindow()==hWnd)?"foreground":"");
		if(gEnv && gEnv->pSystem && gEnv->pSystem->GetISystemEventDispatcher())
		{
			gEnv->pSystem->GetISystemEventDispatcher()->OnSystemEvent(ESYSTEM_EVENT_POS_CHANGED, 1, 0);
		}
		break;
  case WM_STYLECHANGED:
		if (g_debugWindowsMessages && gEnv && gEnv->pLog)
			gEnv->pLog->Log("MSG: WM_STYLECHANGED (%s %s)", (GetFocus()==hWnd)?"focused":"", (GetForegroundWindow()==hWnd)?"foreground":"");
    if(gEnv && gEnv->pSystem && gEnv->pSystem->GetISystemEventDispatcher())
    {
      gEnv->pSystem->GetISystemEventDispatcher()->OnSystemEvent(ESYSTEM_EVENT_STYLE_CHANGED, 1, 0);
    }
		break;
	case WM_INPUTLANGCHANGE:
		if (g_debugWindowsMessages && gEnv && gEnv->pLog)
			gEnv->pLog->Log("MSG: WM_INPUTLANGCHANGE");
		if(gEnv && gEnv->pSystem && gEnv->pSystem->GetISystemEventDispatcher())
		{
			gEnv->pSystem->GetISystemEventDispatcher()->OnSystemEvent(ESYSTEM_EVENT_LANGUAGE_CHANGE, wParam, lParam);
		}
		break;
  }

	return DefWindowProc(hWnd, msg, wParam, lParam);
}