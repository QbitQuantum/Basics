bool Threading::currentThreadIsAudioThread() throw()
{
    Threading::ID audioThreadID = getAudioThreadID();
    return audioThreadID == 0 ? false : audioThreadID == getCurrentThreadID();
}