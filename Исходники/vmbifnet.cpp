    /* find a header */
    const char *find_header(const char *name)
    {
        /* remember the name length */
        size_t namelen = strlen(name);

        /* scan the headers */
        for (const char *p = hdrs ; p != 0 ; p = next_header(p))
        {
            /* skip spaces */
            for ( ; *p != '\0' && is_space(*p) ; ++p) ;

            /* check for a match */
            if (memicmp(p, name, namelen) == 0)
            {
                /* skip the name and any subsequent spaces */
                for (p += namelen ; *p != '\0' && is_space(*p) ; ++p) ;

                /* make sure we have a ':' */
                if (*p == ':')
                {
                    /* skip the ':' and subsequent spaces */
                    for (p += 1 ; *p != '\0' && is_space(*p) ; ++p) ;

                    /* this is the start of the header value */
                    return p;
                }
            }
        }

        /* didn't find it */
        return 0;
    }