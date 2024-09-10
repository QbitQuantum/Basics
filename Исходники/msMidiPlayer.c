void OpenSeq(TSequencer * s, char * n)
{
        midiFILE *      f;
        int             i;
        
 // initialisation
 
 	s->ref = MidiOpen("msMidiPlayer");
        s->state = idle;
        s->seq = MidiNewSeq();
        s->playtask = 0;
	s->looptask = 0;
		
        
 // read the midi file
        
        f = MidiFileOpen(n, MidiFileRead);
		
        if (!f) {
                printf ("Error opening MidiFile %s (%d)\n", n, MidiFile_errno);
                CloseSeq(s);
                exit(MidiFile_errno);
        }
        for (i = f->ntrks; i; i--){ MixSeq( MidiFileReadTrack(f), s->seq); }
	           
        if (smpte(f)) 
                TrsfSmpteSeq(s->seq, frame_par_sec(f), ticks_par_frame(f));
        else
                TrsfTempoSeq(s->seq, ticks_par_quarterNote(f));
	
	if (First(s->seq))
	 	printf("File : %s, Format : %d, Tracks : %d, Length : %d, Duration : %d\n",
                        n, f->format, f->ntrks, LenSeq(s->seq), Date(Last(s->seq)) );
	           
        (void) MidiFileClose(f);
       
 // installation
    	
        MidiSetInfo(s->ref, s);
        MidiSetRcvAlarm(s->ref, NullRcv);
        
        MidiConnect(s->ref, 0, 1);
        MidiConnect(0, s->ref, 1);
}