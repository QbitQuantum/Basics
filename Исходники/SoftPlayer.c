void cSoftPlayer::FileReplay() {
        AVPacket  pkt;
        int ret;
        int PacketCount=0;
        int64_t PTS=0;
        int64_t lastPTS=0;

        pollTimeouts=0;
	pause=false;
	forward=true;
	new_forward=true;
	speed=-1;
	new_speed=-1;
        AudioIdx=-1;
        VideoIdx=-1;
	reading=true;

        OpenFile(filename);
        newFile=false;


        if (!ic) {
	   printf("ic is null!!\n");
	   reading= false;
	   return;
	};

        if (Receiver && (Streams & SOFTDEVICE_VIDEO_STREAM) ) {
                Receiver->StopTransfer();
	        DeviceClear();
        };
        if (Receiver && !(Streams & SOFTDEVICE_VIDEO_STREAM) )
                Receiver->StartTransfer();
       
        ResetDevice(Streams);
        while ( running && reading && !newFile) {
                if ( PollDevice(Streams) ) {
                        //PLDBG("poll timeout!!!\n");
                        pollTimeouts++;
                        if (pollTimeouts > 100) {
                                PLDBG("Too many poll timeouts! Reseting device.\n");
                                ResetDevice(Streams);
                                pollTimeouts=0;
                        };
                        continue;
                } else pollTimeouts=0;

                // seek forward / backward
                if (skip) {
                        PLDBG("player skip %d curr pts: %lld, lastPTS %lld\n",skip,
                                        SoftDevice->GetSTC()/9*1000,lastPTS);
                        //av_seek_frame(ic,-1,
                        //   (SoftDevice->GetSTC()/9+skip*100)*100);
#if LIBAVFORMAT_BUILD > 4618
                        av_seek_frame(ic,-1,
                                        (SoftDevice->GetSTC()/9+skip*10000)*100,
                                        AVSEEK_FLAG_BACKWARD);
#else
                        av_seek_frame(ic,-1,
                                        (SoftDevice->GetSTC()/9+skip*10000)*100);
#endif
                        PLDBG("clear\n");
                        skip=0;
                        ResetDevice(Streams);
                        //SoftDevice->ClearPacketQueue();
                        PLDBG("clear finished\n");
                };

                if ( speed != new_speed ) {
                        PLDBG("speed change\n");
                        ResetDevice(Streams);
                        //  if (new_speed!=-1) 
                        //        av_seek_frame(ic,-1,SoftDevice->GetSTC()/9*100);

                        //                        if (new_speed != -1)
                        //                                cPlayer::DeviceTrickSpeed(2);
                        //                        else cPlayer::DeviceTrickSpeed(1);

                        fast_STC=SoftDevice->GetSTC()/9*100;
                        forward = new_forward;
                        speed = new_speed;
                };

                if ( speed!=-1 ) {
                        int step=5*100000; // 5 zehntel sek.
                        if (!forward)
                                step=-step;
                        fast_STC+=step;
#if LIBAVFORMAT_BUILD > 4618
                        av_seek_frame(ic,-1,fast_STC,
                                        AVSEEK_FLAG_BACKWARD);
#else
                        av_seek_frame(ic,-1,fast_STC);
#endif

                        PKTDBG("fast_STC %lld diff %lld forward %d step %d\n",
                                        fast_STC,PTS-lastPTS,forward,step);
                };

                ret = av_read_frame(ic, &pkt);
                //ret = av_read_packet(ic, &pkt);
                PacketCount++;
                if (ret < 0) {
                        printf("Error (%d) reading packet!\n",ret);
                        reading=false;
                        continue;
                }
                
                if (pause) {
                        FreezeDevice(Streams,1);
                        while (pause && running && reading)
                                usleep(10000);
                        FreezeDevice(Streams,0);
                };
 
                lastPTS=PTS;
                PTS=pkt.pts;

                RemuxAndQueue(pkt);

                if (PacketCount == 200)
                        dump_format(ic, 0, "test", 0);

                // update duration (FIXME does that help?)
                duration=ic->duration;
                int currPos= SoftDevice->GetSTC()*AV_TIME_BASE/(9*10000);
                if (duration<currPos)
                        duration=currPos;
        }
	//if (running) 
	//   DeviceFlush(20000);
	PLDBG("Before FlushDevice %d %d \n",running,newFile);
        if (running && !newFile) {
                FlushDevice(Streams);
        };

        ResetDevice(Streams);

};