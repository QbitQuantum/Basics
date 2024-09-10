long ARX_SPEECH_AddSpeech(Entity * io, const std::string & data, long mood,
                          SpeechFlags flags) {

    if(data.empty()) {
        return -1;
    }

    ARX_SPEECH_ClearIOSpeech(io);

    long num = ARX_SPEECH_GetFree();
    if(num < 0) {
        return -1;
    }

    aspeech[num].exist = 1;
    aspeech[num].time_creation = arxtime.get_updated_ul();
    aspeech[num].io = io; // can be NULL
    aspeech[num].duration = 2000; // Minimum value
    aspeech[num].flags = flags;
    aspeech[num].sample = -1;
    aspeech[num].fDeltaY = 0.f;
    aspeech[num].iTimeScroll = 0;
    aspeech[num].fPixelScroll = 0.f;
    aspeech[num].mood = mood;

    LogDebug("speech \"" << data << '"');

    res::path sample;

    if(flags & ARX_SPEECH_FLAG_NOTEXT) {

        // For non-conversation speech choose a random variant

        long count = getLocalisedKeyCount(data);
        long variant = 1;

        // TODO For some samples there are no corresponding entries
        // in the localization file  (utext_*.ini) -> count will be 0
        // We should probably just count the number of sample files

        if(count > 1) {
            do {
                variant = Random::get(1, count);
            } while(io->lastspeechflag == variant);
            io->lastspeechflag = checked_range_cast<short>(variant);
        }

        LogDebug(" -> " << variant << " / " << count);

        if(variant > 1) {
            sample = data + boost::lexical_cast<std::string>(variant);
        } else {
            sample = data;
        }

    } else {

        std::string _output = getLocalised(data);

        io->lastspeechflag = 0;
        aspeech[num].text.clear();
        aspeech[num].text = _output;
        aspeech[num].duration = max(aspeech[num].duration, (unsigned long)(strlen(_output.c_str()) + 1) * 100);

        sample = data;
    }

    Entity * source = (aspeech[num].flags & ARX_SPEECH_FLAG_OFFVOICE) ? NULL : io;
    aspeech[num].sample = ARX_SOUND_PlaySpeech(sample, source);

    if(aspeech[num].sample == ARX_SOUND_TOO_FAR) {
        aspeech[num].sample = audio::INVALID_ID;
    }

    //Next lines must be removed (use callback instead)
    aspeech[num].duration = (unsigned long)ARX_SOUND_GetDuration(aspeech[num].sample);

    if ((io->ioflags & IO_NPC) && !(aspeech[num].flags & ARX_SPEECH_FLAG_OFFVOICE)) {
        float fDiv = aspeech[num].duration /= io->_npcdata->speakpitch;
        aspeech[num].duration = static_cast<unsigned long>(fDiv);
    }

    if (aspeech[num].duration < 500) aspeech[num].duration = 2000;

    if (ARX_CONVERSATION && io)
        for (long j = 0; j < main_conversation.actors_nb; j++)
            if (main_conversation.actors[j] >= 0 && io == entities[main_conversation.actors[j]])
                main_conversation.current = num;

    return num;
}