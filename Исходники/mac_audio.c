void StreamPropertyListenerProc(void * inClientData,
                                AudioFileStreamID inAudioFileStream,
                                AudioFileStreamPropertyID inPropertyID,
                                UInt32 * ioFlags)
{
    // this is called by audio file stream when it finds property values
    struct audioPlayer* player = (struct audioPlayer*)inClientData;
    OSStatus err = noErr;

//    printf("found property '%c%c%c%c'\n", (inPropertyID>>24)&255, (inPropertyID>>16)&255, (inPropertyID>>8)&255, inPropertyID&255);

    switch (inPropertyID) {
    case kAudioFileStreamProperty_ReadyToProducePackets :
    {
        // the file stream parser is now ready to produce audio packets.
        // get the stream format.
        AudioStreamBasicDescription asbd;
        UInt32 asbdSize = sizeof(asbd);
        err = AudioFileStreamGetProperty(inAudioFileStream, kAudioFileStreamProperty_DataFormat, &asbdSize, &asbd);
        if (err) {
            PRINTERROR("get kAudioFileStreamProperty_DataFormat");
            player->failed = true;
            break;
        }

        //TODO: Is this really right!?!
        player->songDuration = player->waith.contentLength * 2000 / asbd.mSampleRate;
        player->samplerate = asbd.mSampleRate;

        player->packetDuration = asbd.mFramesPerPacket / asbd.mSampleRate;

        // create the audio queue
        err = AudioQueueNewOutput(&asbd, PianobarAudioQueueOutputCallback, player, NULL, NULL, 0, &player->audioQueue);
        if (err) {
            PRINTERROR("AudioQueueNewOutput");
            player->failed = true;
            break;
        }

        // allocate audio queue buffers
        for (unsigned int i = 0; i < kNumAQBufs; ++i) {
            err = AudioQueueAllocateBuffer(player->audioQueue, kAQBufSize, &player->audioQueueBuffer[i]);
            if (err) {
                PRINTERROR("AudioQueueAllocateBuffer");
                player->failed = true;
                break;
            }
        }


        // get the cookie size
        UInt32 cookieSize;
        Boolean writable;
        err = AudioFileStreamGetPropertyInfo(inAudioFileStream, kAudioFileStreamProperty_MagicCookieData, &cookieSize, &writable);
        if (err) {
            PRINTERROR("info kAudioFileStreamProperty_MagicCookieData");
            break;
        }

        // get the cookie data
        void* cookieData = calloc(1, cookieSize);
        err = AudioFileStreamGetProperty(inAudioFileStream, kAudioFileStreamProperty_MagicCookieData, &cookieSize, cookieData);
        if (err) {
            PRINTERROR("get kAudioFileStreamProperty_MagicCookieData");
            free(cookieData);
            break;
        }

        // set the cookie on the queue.
        err = AudioQueueSetProperty(player->audioQueue, kAudioQueueProperty_MagicCookie, cookieData, cookieSize);
        free(cookieData);
        if (err) {
            PRINTERROR("set kAudioQueueProperty_MagicCookie");
            break;
        }

        // listen for kAudioQueueProperty_IsRunning
        err = AudioQueueAddPropertyListener(player->audioQueue, kAudioQueueProperty_IsRunning, AudioQueueIsRunningCallback, player);
        if (err) {
            PRINTERROR("AudioQueueAddPropertyListener");
            player->failed = true;
            break;
        }

        break;
    }
    }
}