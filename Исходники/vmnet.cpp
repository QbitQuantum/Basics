/*
 *   Given an XML buffer, find the end of the <?XML?> header and the start of
 *   the regular XML contents 
 */
const char *TadsXml::strip_xml_header(const char *buf)
{
    const char *p;

    /* skip any initial newlines or whitespace */
    for (p = buf ; isspace(*p) || *p == '\n' || *p == '\r' ; ++p) ;

    /* if it starts with "<?xml", find the end of the directive */
    if (memicmp(p, "<?xml ", 6) == 0)
    {
        int qu;

        /* scan for the matching '>' */
        for (p += 6, qu = 0 ; *p != '\0' ; ++p)
        {
            /* check for quotes */
            if (*p == '"' || *p == '\'')
            {
                /* 
                 *   if we're in a quoted section, and this is the matching
                 *   close quote, leave the quoted section; if we're not in a
                 *   quoted section, this is the opening quote of a quoted
                 *   section 
                 */
                if (qu == 0)
                {
                    /* we weren't in a quoted section, so now we are */
                    qu = *p;
                }
                else if (*p == qu)
                {
                    /* we were in a quoted section, and it's our close quote */
                    qu = 0;
                }
            }
            else if (*p == '?' && *(p+1) == '>')
            {
                /* 
                 *   It's the end of the directive.  Skip the "?>" sequence
                 *   and any subsequent newline characters.  
                 */
                for (p += 2 ; *p == '\n' || *p == '\r' ; ++p) ;

                /* 
                 *   we're now at the start of the XML contents - return the
                 *   current pointer 
                 */
                return p;
            }
        }
    }

    /* 
     *   we either didn't find the start of the <?XML?> directive, or we
     *   couldn't find the end of it - in either case, we don't have a
     *   well-formed directive, so there's nothing to strip: just return the
     *   original buffer 
     */
    return buf;
}