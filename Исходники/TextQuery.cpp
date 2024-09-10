string TextQuery::cleanup_str(const string &word)
{
    string ret;
    for (string::const_iterator it = word.begin(); it != word.end(); ++it) {
        if (!ispunct(*it))
            ret += tolower(*it);
    }
    return ret;
}