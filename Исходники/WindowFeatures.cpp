void processFeaturesString(StringView features, std::function<void(StringView type, StringView value)> callback)
{
    unsigned length = features.length();
    for (unsigned i = 0; i < length; ) {
        // skip to first non-separator
        while (i < length && isSeparator(features[i]))
            ++i;
        unsigned keyBegin = i;

        // skip to first separator
        while (i < length && !isSeparator(features[i]))
            i++;
        unsigned keyEnd = i;

        // skip to first '=', but don't skip past a ','
        while (i < length && features[i] != '=' && features[i] != ',')
            ++i;

        // skip to first non-separator, but don't skip past a ','
        while (i < length && isSeparator(features[i]) && features[i] != ',')
            ++i;
        unsigned valueBegin = i;

        // skip to first separator
        while (i < length && !isSeparator(features[i]))
            ++i;
        unsigned valueEnd = i;

        callback(features.substring(keyBegin, keyEnd - keyBegin), features.substring(valueBegin, valueEnd - valueBegin));
    }
}