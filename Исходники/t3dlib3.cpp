int DSound_Init(void)
{
    // this function initializes the sound system
    static int first_time = 1; // used to track the first time the function
    // is entered

    // test for very first time
    if (first_time)
    {		
        // clear everything out
        memset(sound_fx,0,sizeof(pcm_sound)*MAX_SOUNDS);

        // reset first time
        first_time = 0;

        // create a directsound object
        if (FAILED(DirectSoundCreate(NULL, &lpds, NULL)))
            return(0);

        // set cooperation level
        if (FAILED(lpds->SetCooperativeLevel((HWND)main_window_handle,DSSCL_NORMAL)))
            return(0);

    } // end if

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

    // return sucess
    return(1);

} // end DSound_Init