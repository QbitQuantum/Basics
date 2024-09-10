// MM-2011-03-24: Added.  Displays a balloon popup above the taskbar icon containing the given message and title.
void MCSystemBalloonNotification(MCStringRef p_title, MCStringRef p_message)
{
	// Shell_NotifyIconA uses the cbSize of the struct passed to determine what fields have been set
	// allowing us to use the extended NOTIFYICONDATA500A struct with the extra fields for balloons.
	NOTIFYICONDATA500W t_nidata;
	MCMemoryClear(&t_nidata, sizeof(NOTIFYICONDATA500W));
	t_nidata . cbSize = sizeof(NOTIFYICONDATA500W);

	// Fecth the window handle that we have bound the taskbar icon to.
	// Only one task bar icon has been created within this window hanlde, with ID 1.
	t_nidata . hWnd = ((MCScreenDC *)MCscreen) -> getinvisiblewindow();
	t_nidata . uID = 1;

	// The NIF_INFO flag determines that the popup should be a balloon rather than a tooltip.
	// The NIIF_INFO flag determines that the info (little i) icon should be used in the balloon.
	t_nidata . uFlags = NIF_INFO;
	t_nidata . dwInfoFlags = NIIF_INFO;

    MCAutoStringRefAsWString t_title, t_message;
    
	// We can specify the title (appears in bold next to the icon) and the body of the balloon.
	if (p_title != nil)
    {
        t_title . Lock(p_title);
		MCMemoryCopy(t_nidata . szInfoTitle, *t_title, 63 * sizeof(WCHAR));
    }
	else
		t_nidata . szInfoTitle[0] = '\0';
	if (p_message != nil)
    {
        t_message . Lock(p_message);
		MCMemoryCopy(t_nidata . szInfo, *t_message, 255 * sizeof(WCHAR));
    }
	else
		t_nidata . szInfo[0] = '\0';

	// Call with NIM_MODIFY to flag that we want to update an existing taskbar icon.
	Shell_NotifyIconW(NIM_MODIFY, (PNOTIFYICONDATAW) &t_nidata);
}