void	GUI_MemoryHog::InstallNewHandler(void)
{
	sOldHandler = set_new_handler(GUI_MemoryHog::our_new_handler);
}