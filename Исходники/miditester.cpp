int main(int argc, char* argv[])
{


    char filename[] = "doom-e1m1.mid";
      RtMidiOut *midiout = new RtMidiOut();
    string portName;
    
    nPorts = midiout->getPortCount();
 
    if(argc < 2)    {
        if ( nPorts == 0 )     cout << "No ports available!\n";
        for ( unsigned int i=0; i<nPorts; i++ ) {
            try { portName = midiout->getPortName(i);    }
             catch (RtError &error) {error.printMessage(); }
            cout << "  Output Port #" << i+1 << ": " << portName << '\n';
        }
    }else{
        int port = atoi(argv[1]);
          //midiout->openPort( port );

        cout << "Opening midi" << endl;    
        char *filef = argv[2];
        if(argc == 3)
            parser.Open(filef);
        else
            parser.Open(filename);
    
        tickspersecond = ( (parser.bpm / 30.0) * ( parser.tpb));
        cout << " Ticks per second: " << tickspersecond << endl;
        
        (void) signal(SIGINT, finish);
        tickcount = 0;

        Sequencer sequencers[parser.numtracks];
        SequencerRunning = true;
        for(int i=0;i<parser.numtracks;i++)    {
            sequencers[i].StartSequencer(i, &parser.mididata.tracks[i], port);
            sf::Sleep(0.01f);
        }
        sf::Sleep(1);
        timer.Reset();
        while(run)    {
            timecount = timer.GetElapsedTime();
            tickcount += timecount * tickspersecond;
            timer.Reset();
            //sf::Sleep(0.0001f);
        }
    }
    delete midiout;    
    finish(0);
    return 0;
}