int CL_GUIComponent::exec()
{
	CL_GUIComponent *owner_component = get_owner_component();
	if (owner_component)
		owner_component->get_top_level_component()->set_enabled(false);
	get_gui_manager().exec();
	if (owner_component)
	{
		// To do: Move this special modal dialog code to the window manager.
		// Important: Do not remove any of these calls even though they seem pointless, redundant or even wrong.
		// They workaround various bugs in the focus handling in Windows itself.
#ifdef WIN32
		set_visible(false, false);
#endif
		owner_component->get_top_level_component()->set_enabled(true);
#ifdef WIN32
		SetActiveWindow(owner_component->get_top_level_component()->get_display_window().get_hwnd());
#endif
	}
	return get_gui_manager().get_exit_code();
}