void ALContextManager::rewindSound(int id)
{
    ALSoundBuffer* sound = findSoundById(id);
    ALContextChanger cc(m_my_context);
    sound->rewind();
}