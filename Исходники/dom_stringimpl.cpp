bool DOM::strcasecmp(const DOMStringImpl* a, const DOMStringImpl* b)
{
    if (!(a && b))
        return (a && a->l) || (b && b->l);
    if (a->l != b->l)
        return true;
    QChar* ai = a->s;
    QChar* bi = b->s;
    int l = a->l;
    while (l--) {
        if (*ai != *bi && ai->toLower() != bi->toLower())
            return true;
        ++ai, ++bi;
    }
    return false;
}