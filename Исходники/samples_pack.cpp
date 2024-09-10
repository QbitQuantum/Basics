int ToAT3(short *Source, short *Dest, int Size, int BitRate)
{
    int Src_size;
    int Dest_Size;
    int i;

    Wave_Format.wFormatTag = WAVE_FORMAT_PCM;
    Wave_Format.nChannels = 2;
    Wave_Format.cbSize = 0;
    Wave_Format.wBitsPerSample = 16;
    Wave_Format.nSamplesPerSec = 44100;
    Wave_Format.nBlockAlign = Wave_Format.nChannels * Wave_Format.wBitsPerSample / 8;
    Wave_Format.nAvgBytesPerSec = Wave_Format.nSamplesPerSec * Wave_Format.nBlockAlign;

    At3_Format.wfx.wFormatTag = 0x270;
    At3_Format.wfx.nChannels = 2;
    At3_Format.wfx.nSamplesPerSec = 44100;
    At3_Format.wfx.nAvgBytesPerSec = BitRate * 125;
    switch(BitRate)
    {
        case 66:
            At3_Format.wfx.nBlockAlign = 192;
            break;

        case 105:
            At3_Format.wfx.nBlockAlign = 304;
            break;

        case 132:
            At3_Format.wfx.nBlockAlign = 384;
            break;
    }
    At3_Format.wfx.wBitsPerSample = 0;
    At3_Format.wfx.cbSize = 0xe;
    At3_Format.wRevision = 1;
    At3_Format.nSamplesPerBlock = 0x800;
    At3_Format.abReserved[2] = 1;
    At3_Format.abReserved[4] = 1;
    At3_Format.abReserved[6] = 1;
    acmStreamOpen(&Pack_Stream, NULL, (LPWAVEFORMATEX) &Wave_Format, (LPWAVEFORMATEX) &At3_Format, NULL, 0, 0, 0);

    short *dwSource = (short *) malloc(Size * 2 + 8);
    memset(dwSource, 0, Size * 2 + 8);
    for(i = 0; i < Size / 2; i++)
    {
        dwSource[(i * 2)] = Source[i];
        dwSource[(i * 2) + 1] = 0;
    }

    Source = dwSource;
    Size *= 2;

    Src_size = Size;
    unsigned long rawbufsize = 0;
    acmStreamSize(Pack_Stream, Src_size, &rawbufsize, ACM_STREAMSIZEF_SOURCE);
    Uint8 *Pack_Buf = (Uint8 *) malloc(Src_size + 8);
    memset(Pack_Buf, 0, Src_size + 8);
    Uint8 *rawbuf = (Uint8 *) malloc(rawbufsize + 8);
    memset(rawbuf, 0, rawbufsize + 8);

    ACMSTREAMHEADER Pack_Stream_Head;
    ZeroMemory(&Pack_Stream_Head, sizeof(ACMSTREAMHEADER));
    Pack_Stream_Head.cbStruct = sizeof(ACMSTREAMHEADER);
    Pack_Stream_Head.pbSrc = (Uint8 *) Pack_Buf;
    Pack_Stream_Head.cbSrcLength = Src_size;
    Pack_Stream_Head.pbDst = rawbuf;
    Pack_Stream_Head.cbDstLength = rawbufsize;
    acmStreamPrepareHeader(Pack_Stream, &Pack_Stream_Head, 0);

    memcpy(Pack_Buf, Source, Src_size);

    acmStreamConvert(Pack_Stream, &Pack_Stream_Head, 0);
    Dest_Size = Pack_Stream_Head.cbDstLengthUsed;
    if(Dest_Size < Src_size)
    {
        memcpy(Dest, rawbuf, Dest_Size);
    }
    else
    {
        Dest_Size = 0;
    }

    acmStreamUnprepareHeader(Pack_Stream, &Pack_Stream_Head, 0);
    if(rawbuf) free(rawbuf);
    if(Pack_Buf) free(Pack_Buf);
    if(dwSource) free(dwSource);
    acmStreamClose(Pack_Stream, 0);

    return(Dest_Size);
}