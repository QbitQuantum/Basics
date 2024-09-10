//---------------------------------------------------------------------------
void File_ChannelGrouping::Read_Buffer_Init()
{
    if (Common==NULL)
    {
        Common=new common;
        Common->Parser=new File_Aes3;
        ((File_Aes3*)Common->Parser)->SampleRate=SampleRate;
        ((File_Aes3*)Common->Parser)->ByteSize=ByteDepth*Channel_Total;
        ((File_Aes3*)Common->Parser)->IsAes3=IsAes3;
        Common->Channels.resize(Channel_Total);
        for (size_t Pos=0; Pos<Common->Channels.size(); Pos++)
            Common->Channels[Pos]=new common::channel;
        Element_Code=(int64u)-1;
        Open_Buffer_Init(Common->Parser);
    }

    Accept(); //Forcing acceptance, no possibility to choose something else or detect PCM
    #if MEDIAINFO_DEMUX
         Demux_UnpacketizeContainer=Config->Demux_Unpacketize_Get();
    #endif //MEDIAINFO_DEMUX
}