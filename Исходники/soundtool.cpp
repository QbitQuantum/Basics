void play_sound(short which, short how_many_times) { // if < 0, play asynch
#if defined(__APPLE__)
	Handle sndhandle;
	unsigned long dummy;
	OSErr err;
	SndCommand theCommand;
	if (!play_sounds || how_many_times == 0) return;
	
	if (abs(which) > NUM_SOUNDS) {
		//char msg[50];
		/*s*/printf(/*msg,*/"Error: Sound #%i does not exist.\n",abs(which));
		//give_error(msg,"",0);
		return;
	}
	
	channel++;
	
	if (channel > numchannel) channel = 0;
	
	if (!sound_going(abs(which)) && load_when_play[abs(which)]) 
		sndhandle = GetResource('snd ',20000 + abs(which));
	else sndhandle = sound_handles[abs(which)];
	
	if (which > 0)
 		if (always_asynch[which])
			which *= -1;
	
 	if (sndhandle != NULL)
	{
		HLock(sndhandle);
		
		if (which < 0) err = SndPlay(chan[channel],(SndListHandle) sndhandle,true); // Normal SndPlay
		else {
			err = SndPlay(chan[channel],(SndListHandle) sndhandle,false);
		}
		if (err != 0) {
			printf("Sound error.\n");
			//add_string_to_buf("Sound Error. Error codes:");
			//print_nums(channel,which,err);
			//add_string_to_buf("Your system could not play a sound.");
			//add_string_to_buf("Make sure editor isn't running.");
			//add_string_to_buf("Turn off sounds if necessary.");
		}
		HUnlock(sndhandle);
		snd_played[channel] = abs(which);
		theCommand.cmd = callBackCmd;
		theCommand.param1 = 0;
#ifndef EXILE_BIG_GUNS
		theCommand.param2 = SetCurrentA5();
#endif
#ifdef EXILE_BIG_GUNS
		theCommand.param2 = 0;
#endif
		SndDoCommand(chan[channel],&theCommand,true);
	}
	else SysBeep(20);
	if (which < 0)
		Delay(sound_delay[-1 * which],&dummy);
	if(how_many_times > 1)
		play_sound(which, how_many_times - 1);
#elif defined(WIN32)
	short i,num_fails = 0;
	char snd_name[30];
	bool asyn = false,a_sound_did_get_played = false;
	bool not_asyn = false,check_sound;
	HRSRC h;
	if ((sounds_missing) || (!play_sounds) || (how_many_times == 0))
		return;
	
	if (which < 0) {
		asyn = true;
		which = which * -1;
		}
	if (which >= 1000) {
		which -= 1000;
		not_asyn = true;
		}

	if (which >= 100)
		return;

	if ((always_asynch[which] == true) &&
	((can_ignore[which] == 1) || (can_ignore[which] >= 3)))
		asyn = true;
	if ((can_ignore[which] > 0) && (can_ignore[which] < 5) && (party.stuff_done[305][5] == 1))
		return;
	if ((can_ignore[which] != 1) && (can_ignore[which] < 3))
		asyn = false;
	if ((party.stuff_done[305][5] == 1) && (can_ignore[which] < 5))
		asyn = false;
	if (not_asyn == true)
		asyn = false;

	if ((load_when_play[which] == true) && (sound_handles[which] == NULL)) {
			asyn = false;
		sprintf((char *)snd_name,"#%d",which + 1);
		h = FindResource(hModule,snd_name,"#100");

		sound_handles[which] = LoadResource(hModule,h);
		snds[which] = (char *) LockResource(sound_handles[which]);

		}

	if (store_last_sound_played == 6)
		sndPlaySound(NULL,0);

	if (asyn == true) {
		if (can_ignore[which] >= 4)
			check_sound = sndPlaySound(snds[which],SND_ASYNC | SND_MEMORY | SND_NOSTOP);
			else check_sound = sndPlaySound(snds[which],SND_ASYNC | SND_MEMORY);

		while (check_sound == false) {

			if (can_ignore[store_last_sound_played] == 4) {// then sound goes away
				return;
				}


			num_fails++;
			if (num_fails < 40)
				sound_pause(25);
				else {
					MessageBox(mainPtr,"Cannot play sounds - Sounds stuck error a. Game can still be played, but quietly. Check to make sure your sound drivers are up to date and not corrupted.",
					  "Sound Error",MB_OK | MB_ICONEXCLAMATION);
					print_nums(111,which,num_fails);
					sounds_fucked = true;
					return;
					}
			sndPlaySound(NULL,0);

			if (can_ignore[which] >= 4)
				check_sound = sndPlaySound(snds[which],SND_ASYNC | SND_MEMORY | SND_NOSTOP);
				else check_sound = sndPlaySound(snds[which],SND_ASYNC | SND_MEMORY);
			}
	  a_sound_did_get_played = true;
	  }
		else {
		if (can_ignore[which] >= 4)
			check_sound = sndPlaySound(snds[which],SND_SYNC | SND_MEMORY | SND_NOSTOP);
			else check_sound = sndPlaySound(snds[which],SND_SYNC | SND_MEMORY);
		while (check_sound == false) {
			if (can_ignore[store_last_sound_played] == 4) {// then sound goes away
				return;
				}


			num_fails++;
			if (num_fails < 40)
				sound_pause(25);
				else {
					MessageBox(mainPtr,"Cannot play sounds - Sounds stuck error b. Game can still be played, but quietly. Check to make sure your sound drivers are up to date and not corrupted.",
					 "Sound Error",MB_OK | MB_ICONEXCLAMATION);
					print_nums(222,which,num_fails);
					sounds_fucked = true;
					return;
					}
			sndPlaySound(NULL,0);

			if (can_ignore[which] >= 4)
				check_sound = sndPlaySound(snds[which],SND_SYNC | SND_MEMORY | SND_NOSTOP);
				else check_sound = sndPlaySound(snds[which],SND_SYNC | SND_MEMORY);
			}
		a_sound_did_get_played = true;
	  }

	store_last_sound_played = which;

	if ((load_when_play[which] == true) && (asyn == false)) 
		sound_handles[which] = NULL;
		
	for (i = 0; i < NUM_SOUNDS; i++)
		if ((load_when_play[which] == true) && (sound_handles[which] != NULL)
			&& (a_sound_did_get_played == true) && (i != which))
		{
			sound_handles[i] = NULL;
		}
#endif
}