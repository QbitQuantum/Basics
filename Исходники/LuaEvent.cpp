	BOOL WINAPI DetourWeSetMenu(HWND hWnd, HMENU hMenu)
	{
		if (hWnd == gWeMainWindowHandle)
		{
			gWeMainMenuHandle = hMenu;
			int results = event_array[EVENT_INIT_MENU]([&](lua_State* L, int idx){
				lua_pushstring(L, "main_window_handle");
				lua_pushinteger(L, (lua_Integer)hWnd);
				lua_settable(L, idx);
				lua_pushstring(L, "main_menu_handle");
				lua_pushinteger(L, (lua_Integer)hMenu);
				lua_settable(L, idx);
			});

			// Hook window
			pgTrueWeWindowProc = (decltype(pgTrueWeWindowProc))GetWindowLongPtrA(gWeMainWindowHandle, GWL_WNDPROC);
			SetWindowLongA(gWeMainWindowHandle, GWL_WNDPROC, reinterpret_cast<LONG>(DetourWeWindowProc));
		}

		return base::std_call<BOOL>(pgTrueSetMenu, hWnd, hMenu);
	}