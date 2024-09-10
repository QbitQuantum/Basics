bool OpenAL::CreateContext()
{
    ReleaseContext();

    if(!m_Device)
    {
        LogError("Couldn't create OAL context, device not opened");
        return false;
    }

    m_Context = alcCreateContext(m_Device, NULL);

    if(m_Context)
    {
        LogInfo("Created OAL context");
        alcMakeContextCurrent(m_Context);
    }

    return m_Context != NULL;
}