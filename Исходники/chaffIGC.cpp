void    CchaffIGC::Update(Time now)
{
    float   dtLeft = Seconds(m_timeExpire - now).count();
    if (dtLeft <= 0.0f)
        Terminate();
    else
    {
        float   r = m_pChaffTypeData->radius * (1.0f - dtLeft / m_pChaffTypeData->lifespan);
        SetRadius(r > 1.0f ? r : 1.0f);
        TmodelIGC<IchaffIGC>::Update(now);
    }
}