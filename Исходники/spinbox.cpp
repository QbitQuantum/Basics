void uiSpinboxSetValue(uiSpinbox *s, int value)
{
	s->inhibitChanged = TRUE;
	SendMessageW(s->updown, UDM_SETPOS32, 0, (LPARAM) value);
	s->inhibitChanged = FALSE;
}