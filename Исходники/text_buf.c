/**
 * Concatenate some text to the buf
 * @param tb the text buf in question
 * @param text the text
 * @param len the length of the text
 * @return 1 if it worked, else 0
 */
int text_buf_concat( text_buf *tb, UChar *text, int len )
{
    if ( len+tb->len+1 > tb->allocated )
    {
        int new_size = (tb->len+len+1)*3/2;
        UChar *temp = calloc( new_size, sizeof(UChar) );
        if ( temp == NULL )
        {
            return 0;
        }
        else
        {
            u_strncpy( temp, tb->buf, tb->len );
            free( tb->buf );
            tb->allocated = new_size;
            tb->buf = temp;
        }
    }
    u_strncpy( &tb->buf[tb->len], text, len );
    tb->len += len;
    tb->buf[tb->len] = 0;
    return 1;
}