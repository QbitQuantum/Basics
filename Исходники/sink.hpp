    void Write(StringView data)
    {
        NEPTOOLS_CHECK(SinkOverflow, offset+buf_put+data.length() <= size,
                       "Sink overflow during write");
        auto cp = std::min(data.length(), size_t(buf_size - buf_put));
        memcpy(buf+buf_put, data.data(), cp);
        data.remove_prefix(cp);
        buf_put += cp;

        if (!data.empty()) Write_(data);
    }