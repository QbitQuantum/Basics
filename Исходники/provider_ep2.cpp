/* This only gets called if IServerGameDLL::GetUserMessageInfo() triggers it */
void Detour_Error(const tchar *pMsg, ...)
{
	/* Jump back to setjmp() in CacheUserMessages() */
	longjmp(usermsg_end, 1);
}