void match_verify( match *m, UChar *text, int tlen )
{
    // sanity check match
    match_verify_end( m );
    UChar *copy = calloc( m->len, sizeof(UChar) );
    if ( copy != NULL )
    {
        card *c = m->start.current;
        int i=0;
        int count = 0;
        while ( c != NULL && i <= m->len )
        {
            pair *p = card_pair(c);
            UChar *pdata = pair_data(p);
            if ( m->start.current == m->end.current )
            {
                count = (m->prev.pos-m->start.pos)+1;
                if ( i+count<=m->len )
                    u_memcpy(&copy[i], &pdata[m->start.pos], count);
                i += count;
                break;
            }
            else if ( m->start.current == c )
            {
                count = pair_len(p)-m->start.pos;
                if ( i+count<=m->len )
                    u_memcpy(&copy[i], &pdata[m->start.pos], count);
                i += count;
            }
            else if ( c == m->prev.current )
            {
                count = m->prev.pos+1;
                if ( i+count<=m->len )
                    u_memcpy(&copy[i], pdata, count);
                i += count;
                break;
            }
            else
            {
                count = pair_len(p);
                if ( count>0 && i+count<=m->len )
                    u_memcpy(&copy[i], pdata, count);
                i += count;
            }
            c = card_next( c, m->bs, 0 );
        }
        int j,mend=i;
        int tend = m->text_off+m->len;
        if ( m->len != i )
            printf("match: source %d and dest %d different lengths\n",i,m->len);
        for ( i=0,j=m->text_off;i<mend&&j<tend;i++,j++ )
        {
            if ( text[j] != copy[i] )
            {
                printf("match: mismatch!\n");
                break;
            }
        }
        free( copy );
    }
    if ( m->next != NULL )
        match_verify( m->next, text, tlen );
}