void joy_Update()
{
	JOYINFO ji;
	int result;

	if (!joy_initd) return;
	for (int i=0; i<4; i++)
	{
		if (!sticks[i].active) continue;
		if (result = joyGetPos(joy_sticks[i], &ji) != JOYERR_NOERROR)
			return; // some error,

		sticks[i].left  = (ji.wXpos < sticks[i].range_left);
		sticks[i].right = (ji.wXpos > sticks[i].range_right);
		sticks[i].up    = (ji.wYpos < sticks[i].range_up);
		sticks[i].down  = (ji.wYpos > sticks[i].range_down);

		sticks[i].analog_x = (ji.wXpos * 2000 / sticks[i].xrange) - 1000;
		sticks[i].analog_y = (ji.wYpos * 2000 / sticks[i].yrange) - 1000;

		for (int b=0; b<32; b++)
			sticks[i].button[b] = (ji.wButtons & buttonmask[b]);
	}
}