static LRESULT WINAPI GetMsgProc(int code, WPARAM wParam, LPARAM lParam) {
   return(CallNextHookEx(g_hhook, code, wParam, lParam));
}