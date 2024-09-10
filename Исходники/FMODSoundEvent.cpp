void FMODSoundEvent::GetEventParametersInfo(Vector<SoundEventParameterInfo> & paramsInfo) const
{
    paramsInfo.clear();

    FMOD::Event * event = 0;
    if(fmodEventInstances.size())
    {
        event = fmodEventInstances[0];
    }
    else
    {
        FMOD::EventSystem * fmodEventSystem = SoundSystem::Instance()->fmodEventSystem;
        fmodEventSystem->getEvent(eventName.c_str(), FMOD_EVENT_INFOONLY, &event);
    }

    if(!event)
        return;

    int32 paramsCount = 0;
    FMOD_VERIFY(event->getNumParameters(&paramsCount));
    paramsInfo.reserve(paramsCount);
    for(int32 i = 0; i < paramsCount; i++)
    {
        FMOD::EventParameter * param = 0;
        FMOD_VERIFY(event->getParameterByIndex(i, &param));
        if(!param)
            continue;

        char * paramName = 0;
        FMOD_VERIFY(param->getInfo(0, &paramName));

        SoundEventParameterInfo pInfo;
        pInfo.name = String(paramName);
        FMOD_VERIFY(param->getRange(&pInfo.minValue, &pInfo.maxValue));

        paramsInfo.push_back(pInfo);
    }
}