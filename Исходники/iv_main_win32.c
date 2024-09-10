BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (iv_state_index == -1)
		return TRUE;

	if (fdwReason == DLL_PROCESS_DETACH || fdwReason == DLL_THREAD_DETACH) {
		struct iv_state *st;

		st = iv_get_state();
		if (st != NULL)
			__iv_deinit(st);
	}

	if (fdwReason == DLL_PROCESS_DETACH) {
		TlsFree(iv_state_index);
		iv_state_index = -1;
	}

	return TRUE;
}