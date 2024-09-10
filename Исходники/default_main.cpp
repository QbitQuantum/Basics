static BOOL WINAPI control_handler(DWORD type)
{
	ctx->abort();
	keep_running = false;
	return true;
}