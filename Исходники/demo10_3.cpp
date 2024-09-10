int Game_Init(void *parms)
{
// this function is where you do all the initialization 
// for your game

// create a directsound object
if (DirectSoundCreate(NULL, &lpds, NULL)!=DS_OK )
	return(0);

// set cooperation level
if (lpds->SetCooperativeLevel(main_window_handle,DSSCL_NORMAL)!=DS_OK)
	return(0);

// clear array out
memset(sound_fx,0,sizeof(pcm_sound)*MAX_SOUNDS);
	
// initialize the sound fx array
for (int index=0; index<MAX_SOUNDS; index++)
	{
	// test if this sound has been loaded
	if (sound_fx[index].dsbuffer)
		{
		// stop the sound
		sound_fx[index].dsbuffer->Stop();

		// release the buffer
		sound_fx[index].dsbuffer->Release();
	
		} // end if

	// clear the record out
	memset(&sound_fx[index],0,sizeof(pcm_sound));

	// now set up the fields
	sound_fx[index].state = SOUND_NULL;
	sound_fx[index].id    = index;

	} // end for index

// load a wav file in
if ((sound_id = DSound_Load_WAV("FLIGHT.WAV"))!=-1)
   {
   // start the voc playing in looping mode
   sound_fx[sound_id].dsbuffer->Play(0,0,DSBPLAY_LOOPING);
   } // end if

// return success
return(1);

} // end Game_Init