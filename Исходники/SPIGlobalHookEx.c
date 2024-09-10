HHOOK WINAPI DllWindowsHookExW(UINT idHook)
{

	switch(	idHook )
	{
	case WH_CBT:
		if (HHOOKA) return 0;
		HHOOKA = SetWindowsHookExW(idHook,CBTProc,ihinstDLL,0);
		if (HHOOKA) return HHOOKA;
		break;
	case WH_DEBUG:
		if (HHOOKB) return 0;
		HHOOKB = SetWindowsHookExW(idHook,DebugProc,ihinstDLL,0);
		if (HHOOKB) return HHOOKB;
		break;
	case WH_FOREGROUNDIDLE:
		if (HHOOKC) return 0;
		HHOOKC = SetWindowsHookExW(idHook,ForegroundIdleProc,ihinstDLL,0);
		if (HHOOKC) return HHOOKC;
		break;
	case WH_GETMESSAGE:
		if (HHOOKD) return 0;
		HHOOKD = SetWindowsHookExW(idHook,GetMsgProc,ihinstDLL,0);
		if (HHOOKD) return HHOOKD;
		break;
	case WH_KEYBOARD:
		if (HHOOKE) return 0;
		HHOOKE = SetWindowsHookExW(idHook,KeyboardProc,ihinstDLL,0);
		if (HHOOKE) return HHOOKE;
		break;
	case WH_MOUSE:
		if (HHOOKF) return 0;
		HHOOKF = SetWindowsHookExW(idHook,MouseProc,ihinstDLL,0);
		if (HHOOKF) return HHOOKF;
		break;
	case WH_MSGFILTER:
		if (HHOOKG) return 0;
		HHOOKG = SetWindowsHookExW(idHook,MessageProc,ihinstDLL,0);
		if (HHOOKG) return HHOOKG;
		break;
	case WH_SHELL:
		if (HHOOKH) return 0;
		HHOOKH = SetWindowsHookExW(idHook,ShellProc,ihinstDLL,0);
		if (HHOOKH) return HHOOKH;
		break;
	case WH_KEYBOARD_LL:
		if (HHOOKI) return 0;
		HHOOKI = SetWindowsHookExW(idHook,KeyboardLLProc,ihinstDLL,0);
		if (HHOOKI) return HHOOKI;
		break;
	case WH_MOUSE_LL:
		if (HHOOKJ) return 0;
		HHOOKJ = SetWindowsHookExW(idHook,MouseLLProc,ihinstDLL,0);
		if (HHOOKJ) return HHOOKJ;
		break;
	default:
		return 0;
		break;
	}

	return 0;

}