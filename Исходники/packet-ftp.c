/*
 * RFC2428 states...
 *
 *     AF Number   Protocol 
 *     ---------   --------         
 *     1           Internet Protocol, Version 4 
 *     2           Internet Protocol, Version 6 
 *     
 *     AF Number   Address Format      Example         
 *     ---------   --------------      -------         
 *     1           dotted decimal      132.235.1.2         
 *     2           IPv6 string         1080::8:800:200C:417A                     
 *                 representations                     
 *                 defined in 
 *     
 *     The following are sample EPRT commands:         
 *          EPRT |1|132.235.1.2|6275|         
 *          EPRT |2|1080::8:800:200C:417A|5282|
 *     
 *     The first command specifies that the server should use IPv4 to open a    
 *     data connection to the host "132.235.1.2" on TCP port 6275.  The    
 *     second command specifies that the server should use the IPv6 network    
 *     protocol and the network address "1080::8:800:200C:417A" to open a    
 *     TCP data connection on port 5282.
 * 
 * ... which means in fact that RFC2428 is capable to handle both, 
 * IPv4 and IPv6 so we have to care about the address family and properly
 * act depending on it.
 * 
 */
static gboolean
parse_eprt_request(const guchar* line, gint linelen, guint32 *eprt_af, 
        guint32 *eprt_ip, guint16 *eprt_ipv6, guint16 *ftp_port, 
        guint32 *eprt_ip_len, guint32 *ftp_port_len) 
{
    gint      delimiters_seen = 0;
    gchar     delimiter;
    gint      fieldlen;
    gchar    *field;
    gint      n;
    gint      lastn;
    char     *args, *p;
    gboolean  ret = TRUE;


    if (!line)
        return FALSE;
    /* Copy the rest of the line into a null-terminated buffer. */
    args = ep_strndup(line, linelen);
    p = args;

    /*
     * RFC2428 sect. 2 states ...
     * 
     *     The EPRT command keyword MUST be followed by a single space (ASCII
     *     32). Following the space, a delimiter character (<d>) MUST be
     *     specified.
     *
     * ... the preceding <space> is already stripped so we know that the first
     * character must be the delimiter and has just to be checked to be valid.
     */
    if (!isvalid_rfc2428_delimiter(*p))
        return FALSE;  /* EPRT command does not follow a vaild delimiter;
                        * malformed EPRT command - immediate escape */

    delimiter = *p; 
    /* Validate that the delimiter occurs 4 times in the string */
    for (n = 0; n < linelen; n++) {
        if (*(p+n) == delimiter) 
            delimiters_seen++;
    }
    if (delimiters_seen != 4)
        return FALSE; /* delimiter doesn't occur 4 times 
                       * probably no EPRT request - immediate escape */

    /* we know that the first character is a delimiter... */
    delimiters_seen = 1;
    lastn = 0;
    /* ... so we can start searching from the 2nd onwards */
    for (n=1; n < linelen; n++) {

        if (*(p+n) != delimiter)
            continue;

        /* we found a delimiter */
        delimiters_seen++;

        fieldlen = n - lastn - 1;
        if (fieldlen<=0)
            return FALSE; /* all fields must have data in them */
        field =  p + lastn + 1;

        if (delimiters_seen == 2) {     /* end of address family field */
            gchar *af_str;
            af_str = ep_strndup(field, fieldlen);
            *eprt_af = atoi(af_str);
        }
        else if (delimiters_seen == 3) {/* end of IP address field */
            gchar *ip_str;
            ip_str = ep_strndup(field, fieldlen);

            if (*eprt_af == EPRT_AF_IPv4) {
                if (inet_pton(AF_INET, ip_str, eprt_ip) == 1)
                   ret = TRUE;
                else
                   ret = FALSE;
            }
            else if (*eprt_af == EPRT_AF_IPv6) {
                if (inet_pton(AF_INET6, ip_str, eprt_ipv6) == 1)
                   ret = TRUE;
                else
                   ret = FALSE;
            }
            else
                return FALSE; /* invalid/unknown address family */

            *eprt_ip_len = fieldlen;
        }
        else if (delimiters_seen == 4) {/* end of port field */
            gchar *pt_str;
            pt_str = ep_strndup(field, fieldlen);

            *ftp_port = atoi(pt_str);
            *ftp_port_len = fieldlen;
        }

        lastn = n;
    }

    return ret;
}