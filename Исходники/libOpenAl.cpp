OPAL_SOUND_MGR void SoundManager::trimTrailingSpace( char *s )
{
	char *p;
	p = s;
	if (p == NULL) return;
	for (unsigned i=0;i < (strlen(s)+1);i++)
	{
		if (__iscsym(*p) == 0 && *p != '.' && *p != '-')
		{
			*p='\0';
			break;
		}
		p++;
	}
}