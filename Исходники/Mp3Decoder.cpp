void Mp3Decoder::OpenFile()
{
    GuardPtr = NULL;
    ReadBuffer = (u8 *) memalign(32, SoundBlockSize*SoundBlocks);
    if(!ReadBuffer)
    {
        if(file_fd)
            delete file_fd;
        file_fd = NULL;
        return;
    }

    u8 dummybuff[4096];
    int ret = Read(dummybuff, 4096, 0);
    if(ret <= 0)
    {
        if(file_fd)
            delete file_fd;
        file_fd = NULL;
        return;
    }

    SampleRate = (u32) Frame.header.samplerate;
    Format = ((MAD_NCHANNELS(&Frame.header) == 2) ? VOICE_STEREO_16BIT : VOICE_MONO_16BIT);
    Rewind();
    Decode();
}