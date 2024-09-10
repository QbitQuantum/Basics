bool fini_state(program_state_t * state)
{
	if (state->addrinfo == NULL) {
		FreeAddrInfo(state->addrinfo);
	}
	if (state->exit_evt != NULL) {
		CloseHandle(state->exit_evt);
	}
	if (state->tpool != (TPHANDLE)-1) {
		StopThreadPool(state->tpool, 2 * 60 * 1000);
	}
	return true;
}