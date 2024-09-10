XAudio2SoundDevice::XAudio2SoundDevice() :
    SoundDevice(SOUNDDEVICE_XAUDIO2), Device_(0), MasterVoice_(0)
{
    /* Initialize XAudio2 */
    #ifndef SP_PLATFORM_XBOX
    CoInitializeEx(0, COINIT_MULTITHREADED);
    #endif
    
    /* Create XAudio2 device */
    UINT32 Flags = 0;
    
    #ifdef _DEBUG
    Flags |= XAUDIO2_DEBUG_ENGINE;
    #endif
    
    if (XAudio2Create(&Device_, Flags) != S_OK)
    {
        io::Log::error("Could not create XAudio2 device");
        return;
    }
    
    /* Create mastering voice */
    if (Device_->CreateMasteringVoice(&MasterVoice_) != S_OK)
    {
        io::Log::error("Could not create mastering voice");
        return;
    }
}