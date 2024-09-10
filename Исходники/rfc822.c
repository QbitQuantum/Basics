/****************
 * Add header lines to the existing ones.
 * Such a line may include LFs which are used to split the line
 * int several fields.	This must be a valid header line.
 */
int
rfc822_add_header( RFC822 msg, const char *line )
{
    HDR_LINE hdr;
    const char *lf;
    size_t n;
    int do_cb;

    /* send the notification only if we have not processed all header lines */
    do_cb = !msg->in_body && strlen(line) >= 9 && !memicmp(line, "Received:", 9);

    do {
        lf = strchr( line, '\n' );
        n = lf? ( lf - line ) : strlen( line );
        hdr = malloc( sizeof( *hdr ) + n );
        if( !hdr )
            return RFC822ERR_NOMEM;
        hdr->next = NULL;
        hdr->cont = (*line == ' ' || *line == '\t');
        memcpy(hdr->line, line, n );
        hdr->line[n] = 0;

        *msg->hdr_lines_head = hdr;
        msg->hdr_lines_head = &hdr->next;
    } while( lf && *(line=lf+1) );

    if( do_cb )
        do_callback( msg, RFC822EVT_RCVD_SEEN );

    return 0;
}