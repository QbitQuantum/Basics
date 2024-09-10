int joystickInit(void)		
{
	int i;

	numJoySticks = joyGetNumDevs();
	if(numJoySticks)
		joySticks = calloc(numJoySticks,sizeof(JOYCAPS));
	for(i=0;i<numJoySticks; i++)
		joyGetDevCaps(i,&(joySticks[i]),sizeof(JOYCAPS));
	return 1;
}