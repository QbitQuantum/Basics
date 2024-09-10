//----------------------------------------------------------------------------
int KeyToModifier(unsigned * eventType,
			  unsigned * addFlags,
			  unsigned * key,
			  unsigned desired_flags,
			  unsigned desired_key,
			  unsigned desired_eventType)
{
	if (*eventType == KEY_DOWN)
	{
		*addFlags |= desired_flags;
		*key = desired_key;
		*eventType = desired_eventType;
	}
	else if (*eventType == KEY_UP)
	{
		REMOVE(*addFlags, desired_flags);
		*key = desired_key;
		*eventType = desired_eventType;
	}
	return 0;
}