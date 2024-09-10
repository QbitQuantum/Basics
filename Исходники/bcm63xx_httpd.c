/***************************************************************************
 * Function Name: read_remaining_hdrs
 * Description  : This function reads the remaining HTTP headers.
 * Returns      : 1 - Remaining headers were read, 0 - were not read.
 ***************************************************************************/
static int read_remaining_hdrs(int s, unsigned char *web_buf, int web_buf_size,
    int *web_buf_idx_ptr, int *close_tcp_ptr, int *content_length_ptr)
{
    int ret = 0;
    int sts = WEB_GETS_DONE;

    while( sts == WEB_GETS_DONE )
    {
        sts = cfe_web_gets( web_buf, web_buf_size, web_buf_idx_ptr, s );
        switch( sts )
        {
        case WEB_GETS_DONE:
            if( *web_buf_idx_ptr == 0 )
            {
                /* The remaining HTTP headers have been read. */
                ret = 1;
                sts = WEB_GETS_PENDING;
            }
            else
            {
                char *p2 = web_buf;
                char *p1 = gettoken(&p2);
                if( !strcmpi( p1, "Content-Length:" ) )
                    *content_length_ptr=atoi(p2);
                *web_buf_idx_ptr = 0;
            }
            break;

        case WEB_GETS_ERROR:
            console_log("web error: TCP read error.");
            *close_tcp_ptr = 1;
            break;
        }
    }

    return( ret );
} /* read_remaining_hdrs */