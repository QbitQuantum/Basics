bool QueryJob::write(const String &out, Flags<WriteFlag> flags)
{
    if ((mJobFlags & WriteUnfiltered) || (flags & Unfiltered) || filter(out)) {
        if ((mJobFlags & QuoteOutput) && !(flags & DontQuote)) {
            String o((out.size() * 2) + 2, '"');
            char *ch = o.data() + 1;
            int l = 2;
            for (int i=0; i<out.size(); ++i) {
                const char c = out.at(i);
                if (c == '"') {
                    *ch = '\\';
                    ch += 2;
                    l += 2;
                } else {
                    ++l;
                    *ch++ = c;
                }
            }
            o.truncate(l);
            return writeRaw(o, flags);
        } else {
            return writeRaw(out, flags);
        }
    }
    return true;
}