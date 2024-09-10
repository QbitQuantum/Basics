void FmodAudioPlayer::init()
{
    //init
    FMOD_RESULT        result;
    FMOD::ChannelGroup *masterChannelGroup;

    unsigned int version;

    /*
     * Create a System object and initialize.
     */
    result = FMOD::System_Create(&pSystem);
    ERRCHECKWITHEXIT(result);

    result = pSystem->setOutput(FMOD_OUTPUTTYPE_ALSA);
    ERRCHECKWITHEXIT(result);

    result = pSystem->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECKWITHEXIT(result);

    result = pSystem->createChannelGroup("Channel Group", &pChannelGroup);
    ERRCHECKWITHEXIT(result);

    result = pSystem->getMasterChannelGroup(&masterChannelGroup);
    ERRCHECKWITHEXIT(result);

    result = masterChannelGroup->addGroup(pChannelGroup);
    ERRCHECKWITHEXIT(result);

    mapEffectSound.clear();
}