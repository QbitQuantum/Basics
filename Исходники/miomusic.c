static void	MyParsePlayString (const OOTstring pmPlayStr,
				   TONE_RECORD pmToneList [],
				   int *pmNumTones)
{
    #define NUM_NOTE_TYPES	6

    char    	*myPtr = pmPlayStr;
    char    	myChar;
    int	    	myNoteInd, myNote;
    int		cnt;
    static char stMyNoteCode [NUM_NOTE_TYPES] = 
			    { '1', '2', '4', '8', '6', '3' };

    *pmNumTones = 0;

    while (*myPtr != 0) 
    {
	myChar = tolower (*myPtr);

	if (isdigit (myChar)) 
	{
            cnt = 0;

	    while ((cnt < NUM_NOTE_TYPES) && (myChar != stMyNoteCode [cnt]))
	    {
		cnt++;
	    }

	    if (cnt == NUM_NOTE_TYPES) 
	    {
		SET_ERRNO(E_MUSIC_BAD_PLAY_CHAR);
	    }
	    else 
	    {
		stNoteDiv = (1 << cnt);
	    }
	}
	else if (('a' <= myChar) && (myChar <= 'g'))
	{
	    myNoteInd = 
		((( myChar < 'c' ) ? (myChar - 'a' + 5) : (myChar - 'c')));
	    myNote = stToneBase [myNoteInd];

	    // Check for flat or sharp
	    if (*(myPtr + 1) == '-') 
	    {
		myNote--;
		myPtr++;
	    }
	    else if (*(myPtr + 1) == '+') 
	    {
		myNote++;
		myPtr++;
	    }

	    // Fill in a tone record

	    pmToneList [*pmNumTones].midiTone = (myNote - 1) + stOctave * 12;
	    pmToneList [*pmNumTones].freq =
		FREQ_FACTOR / (stToneDivisor [myNote] / ( 1 << stOctave ));
	    pmToneList [*pmNumTones].duration = stWholeNoteDuration / stNoteDiv;
	    pmToneList [*pmNumTones].volume = stVolume;
	    (*pmNumTones)++;
	}
	else if (myChar == 'p') 
	{
	    // Fill in a tone record
	    pmToneList [*pmNumTones].midiTone = -1;
	    pmToneList [*pmNumTones].freq = 0;
	    pmToneList [*pmNumTones].duration = stWholeNoteDuration / stNoteDiv;
	    pmToneList [*pmNumTones].volume = 0;
	    (*pmNumTones)++;
	}
	else if (myChar == '<') 
	{
	    // Down one octave
	    if (stOctave > 1)
	    {
	        stOctave--;
	    }
	}
	else if (myChar == '>') 
	{
	    // Up one octave
	    if (stOctave < 8)
	    {
	        stOctave++;
	    }
	}
	else 
	{
	    SET_ERRNO (E_MUSIC_BAD_PLAY_CHAR);
	}
	myPtr++;
    }
    #undef NUM_NOTE_TYPES
} // MyParsePlayString