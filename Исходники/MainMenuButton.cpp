void MainMenuButton::onBlur(wxFocusEvent& event)
{
#ifdef WIN32
	EndMenu();
#endif
}