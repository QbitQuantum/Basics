		void uninstallHooks()
		{
			UnhookWinEvent(g_compatGdiCaretLocationChangeEventHook);
			UnhookWinEvent(g_compatGdiCaretGeneralEventHook);
		}