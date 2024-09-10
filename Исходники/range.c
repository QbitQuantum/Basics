/**
 * Add some content to a removed range
 * @param r the range in question
 * @param s the content
 * @param len its length
 */
void range_add_content( range *r, const UChar *s, int len )
{
    if ( r->content_len > 0 )
    {
        UChar *new_content = calloc( r->content_len+len+1, sizeof(UChar) );
        if ( new_content == NULL )
            error( "range: failed to reallocate content\n");
        else
        {
            u_strncpy( new_content, r->content, r->content_len );
            u_strncpy( &new_content[r->content_len], s, len );
            new_content[r->content_len+len] = 0;
            free( r->content );
            r->content = new_content;
            r->content_len += len;
            //printf("content now %s\n",r->content );
        }
    }
    else
    {
        r->content = calloc( len+1, sizeof(UChar) );
        if ( r->content == NULL )
            error( "range: failed to allocate new content\n");
        u_strncpy( r->content, s, len );
        r->content[len] = 0;
        r->content_len = len;
        // printf("created content length %d\n",len);
    }
}