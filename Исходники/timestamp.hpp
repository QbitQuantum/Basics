    /**
     * Return UTC Unix time as string in ISO date/time format.
     */
    std::string to_iso() const {
        if (m_timestamp == 0) {
            return std::string("");
        }
        struct tm tm;
        time_t sse = seconds_since_epoch();
#ifndef _MSC_VER
        gmtime_r(&sse, &tm);
#else
        gmtime_s(&tm, &sse);
#endif

        std::string s(timestamp_length, '\0');
        /* This const_cast is ok, because we know we have enough space
           in the string for the format we are using (well at least until
           the year will have 5 digits). And by setting the size
           afterwards from the result of strftime we make sure thats set
           right, too. */
        s.resize(strftime(const_cast<char*>(s.c_str()), timestamp_length, timestamp_format(), &tm));
        return s;
    }