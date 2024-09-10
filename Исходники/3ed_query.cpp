void TextQuery::strip_caps(string &line)
{
    // not changing the size of line, so safe to cache the size
    str_size sz = line.size();
    for (str_size pos = 0; pos != sz; ++pos)
        line[pos] = tolower(line[pos]);
}