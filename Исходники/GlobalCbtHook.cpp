void UninitializeGetMsgHook()
{
	if (hookGetMsg != NULL)
		UnhookWindowsHookEx(hookGetMsg);
	hookGetMsg = NULL;
}