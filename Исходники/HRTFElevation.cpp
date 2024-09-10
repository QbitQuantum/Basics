// Lazily load a concatenated HRTF database for given subject and store it in a
// local hash table to ensure quick efficient future retrievals.
static PassRefPtr<AudioBus> getConcatenatedImpulseResponsesForSubject(const String& subjectName)
{
    typedef HashMap<String, RefPtr<AudioBus>> AudioBusMap;
    DEFINE_THREAD_SAFE_STATIC_LOCAL(AudioBusMap, audioBusMap, new AudioBusMap());
    DEFINE_THREAD_SAFE_STATIC_LOCAL(Mutex, mutex, new Mutex());

    MutexLocker locker(mutex);
    RefPtr<AudioBus> bus;
    AudioBusMap::iterator iterator = audioBusMap.find(subjectName);
    if (iterator == audioBusMap.end()) {
        RefPtr<AudioBus> concatenatedImpulseResponses(AudioBus::loadPlatformResource(subjectName.utf8().data(), ResponseSampleRate));
        ASSERT(concatenatedImpulseResponses);
        if (!concatenatedImpulseResponses)
            return nullptr;

        bus = concatenatedImpulseResponses;
        audioBusMap.set(subjectName, bus);
    } else
        bus = iterator->value;

    size_t responseLength = bus->length();
    size_t expectedLength = static_cast<size_t>(TotalNumberOfResponses * ResponseFrameSize);

    // Check number of channels and length. For now these are fixed and known.
    bool isBusGood = responseLength == expectedLength && bus->numberOfChannels() == 2;
    ASSERT(isBusGood);
    if (!isBusGood)
        return nullptr;

    return bus;
}