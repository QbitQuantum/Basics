static EHost_Match s_Match(const char* env,
                           const char* arg, size_t arglen,
                           const char* val, size_t vallen,
                           const char** a, char** v)
{
    int/*bool*/ wildcard = 0/*false*/;
    int/*bool*/ noval = 0/*false*/;
    int/*bool*/ only = 0/*false*/;
    const char* c = env;

    assert(arg  &&  arglen);
    assert(a  &&  !*a  &&  v  &&  !*v);
    /* Note 1:  val == NULL implies vallen == 0, and means there was
     *          no argument in the query;
     * Note 2:  val != NULL does not imply vallen != 0, but means there
     *          was (perhaps, empty [if vallen == 0]) argument in the query.
     */
    while (c) {
        const char* p = strchr(c == env ? c : ++c, '=');
        const char* q = c;
        if (!p)
            break;
        c = strchr(q, '\n');
        if ((size_t)(p - q) != arglen)
            continue;
        if (strncasecmp(q, arg, arglen) != 0)
            continue;
        /* arg matches */
        *a = arg;
        if (memchr(p + 1, '!', (c ? (size_t)(c - p) : strlen(p)) - 1))
            only = 1/*true*/;
        for (q = p+1/*=*/ + strspn(p+1, " \t!"); ; q = p + strspn(p, " \t!")) {
            int/*bool*/ no = 0/*false*/;
            size_t len;
            if (*q != '\0'  &&  *q != '\n')
                len = strcspn(q, " \t!");
            else if (*p == '=')
                len = 0;
            else
                break;
            if (len  &&  *q == '~') {
                no = 1/*true*/;
                len--;
                q++;
            }
            if (len == 1  &&  *q == '*') {
                if (!no)
                    wildcard = 1/*true*/;
            } else if (len == 1  &&  *q == '-') {
                if (!val) {
                    if (no)
                        return eHost_BadMatch;
                    *v = strndup("-", 1);
                    return eHost_BestMatch;
                }
                if (no)
                    wildcard = 1/*true*/;
                else
                    noval = 1/*true*/;
            } else {
                size_t vlen = len;
                if (vlen == 2  &&  q[0] == '"'  &&  q[1] == '"')
                    vlen = 0;
                if (val  &&  vlen == vallen  &&  !strncasecmp(q, val, vlen)) {
                    if (no)
                        return eHost_BadMatch;
                    *v = strndup(q, vlen);
                    return eHost_BestMatch;
                }
                if (no)
                    wildcard = 1/*true*/;
            }
            p = q + len;
        }
    }
    /* Neither best match nor mismatch found */
    if (val) {
        if (wildcard) {
            *v = strndup("*", 1);
            return eHost_GoodMatch;
        }
        if (only)
            return eHost_BadMatch;
        if (!*a)
            return eHost_FairMatch;
        if (noval) {
            *v = strndup("",  0);
            return eHost_PoorMatch;
        }
        return eHost_NoMatch;
    }
    if (!*a)
        return eHost_GoodMatch;
    if (only)
        return eHost_BadMatch;
    if (wildcard) {
        *v = strndup("*", 1);
        return eHost_FairMatch;
    }
    assert(!noval);
    return eHost_PoorMatch;
}