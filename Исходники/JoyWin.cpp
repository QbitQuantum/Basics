void
JoyWin::_ShowNoCompatibleJoystickMessage()
{
	BString str("There were no compatible joysticks detected on this game");
	str << " port. Try another port, or ask the manufacturer of your joystick";
	str << " for a driver designed for Haiku or BeOS.";

	BAlert *alert = new BAlert("test1", str.String(), "OK");
	alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
	alert->Go();
}