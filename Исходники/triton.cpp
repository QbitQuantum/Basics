void HitKey(unsigned char cKey, unsigned int iTimes)
{
	for(unsigned int i = 0; i < iTimes; ++i)
	{
		keybd_event(cKey, 0, 0, 0);
		keybd_event(cKey, 0, KEYEVENTF_KEYUP, 0);
	}
}