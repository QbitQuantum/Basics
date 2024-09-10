static inline void cleanPath(Vector<UChar, 512>& path)
{
    // FIXME: Should not do this in the query or anchor part.
    size_t pos;
    while ((pos = findSlashDotDotSlash(path.data(), path.size())) != notFound) {
        size_t prev = reverseFind(path.data(), path.size(), '/', pos - 1);
        // don't remove the host, i.e. http://foo.org/../foo.html
        if (prev == notFound || (prev > 3 && path[prev - 2] == ':' && path[prev - 1] == '/'))
            path.remove(pos, 3);
        else
            path.remove(prev, pos - prev + 3);
    }

    // FIXME: Should not do this in the query part.
    pos = 0;
    if ((pos = findSlashSlash(path.data(), path.size(), pos)) != notFound) {
        size_t refPos = find(path.data(), path.size(), '#');
        while (refPos == 0 || refPos == notFound || pos < refPos) {
            if (pos == 0 || path[pos - 1] != ':')
                path.remove(pos);
            else
                pos += 2;
            if ((pos = findSlashSlash(path.data(), path.size(), pos)) == notFound)
                break;
        }
    }

    // FIXME: Should not do this in the query or anchor part.
    while ((pos = findSlashDotSlash(path.data(), path.size())) != notFound)
        path.remove(pos, 2);
}