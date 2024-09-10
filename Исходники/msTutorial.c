void test21 ()
{
        long    n;
        
        printf("\n\n<TEST 21> record and playback a sequence\n");
        DebugStr ("--> use g or G to start recording\n");

        ourSequence = MidiNewSeq();
    	ourFilter = MidiNewFilter();
        InstallFilter(ourRefNum,ourFilter);
        MidiFlushEvs(ourRefNum);
        MidiSetRcvAlarm(ourRefNum, record);
        MidiConnect(0, ourRefNum, true);
        MidiConnect(ourRefNum, 0, true);
        
        printf("Now play on the Midi keyboard, every thing is recorded\n");
        DebugStr ("--> use g or G to stop recording\n");

        MidiConnect(0, ourRefNum, false);
        MidiSetRcvAlarm(ourRefNum, 0);
        
        printf (" %ld events where recorded\n", size(ourSequence));

        DebugStr ("--> use g or G to play back the sequence\n");

        stopFlag = 0;
        if (FirstEv(ourSequence)) {
                MidiCall(play, MidiGetTime(), ourRefNum, (long) FirstEv(ourSequence), 0, 0);
        }
        
        printf("Now playing the sequence\n");
        DebugStr ("--> use g or G to stop play back and go to the next test\n");
        
        stopFlag = 1;
        MidiFreeSeq(ourSequence);
}