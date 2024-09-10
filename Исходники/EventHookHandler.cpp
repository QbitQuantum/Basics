void EventHookHandler::UnregisterHook(HWINEVENTHOOK hook)
{
	if (hook)
		UnhookWinEvent(hook);
}