static bool isPrefixOf(const QString &prefix, const QString &what)
{
    return ((what.length() > prefix.length())
            && what.startsWith(prefix));
}