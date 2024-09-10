    static std::tm millisToLocal (int64 millis) noexcept
    {
       #if JUCE_WINDOWS && JUCE_MINGW
        time_t now = (time_t) (millis / 1000);
        return *localtime (&now);

       #elif JUCE_WINDOWS
        std::tm result;
        millis /= 1000;

        if (_localtime64_s (&result, &millis) != 0)
            zerostruct (result);

        return result;

       #else
        std::tm result;
        time_t now = (time_t) (millis / 1000);

        if (localtime_r (&now, &result) == nullptr)
            zerostruct (result);

        return result;
       #endif
    }