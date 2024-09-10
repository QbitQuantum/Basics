static inline bool hostIsInDomain(StringView host, StringView domain)
{
    if (!host.endsWithIgnoringASCIICase(domain))
        return false;

    ASSERT(host.length() >= domain.length());
    unsigned suffixOffset = host.length() - domain.length();
    return suffixOffset == 0 || host[suffixOffset - 1] == '.';
}