void MCThreadCleanupFn()
{
	g_MCThreadExitEvent.SetEvent();
}