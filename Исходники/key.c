void key_flush()
{
	int i;
	fix CurTime;

	_disable();

	// Clear the BIOS buffer
	key_clear_bios_buffer();

	key_data.keyhead = key_data.keytail = 0;

	//Clear the keyboard buffer
	for (i=0; i<KEY_BUFFER_SIZE; i++ )	{
		key_data.keybuffer[i] = 0;
		key_data.time_pressed[i] = 0;
	}
	
	//Clear the keyboard array

	CurTime =timer_get_fixed_secondsX();

	for (i=0; i<256; i++ )	{
		keyd_pressed[i] = 0;
		key_data.TimeKeyWentDown[i] = CurTime;
		key_data.TimeKeyHeldDown[i] = 0;
		key_data.NumDowns[i]=0;
		key_data.NumUps[i]=0;
	}
	_enable();
}