/* Decode an item via the fish 1.x format. Adapted from fish 1.x's item_get(). */
history_item_t history_t::decode_item_fish_1_x(const char *begin, size_t length) {

    const char *end = begin + length;
    const char *pos=begin;

    bool was_backslash = 0;
    wcstring out;
    bool first_char = true;
    bool timestamp_mode = false;
    time_t timestamp = 0;
    
    while( 1 )
    {
        wchar_t c;
        mbstate_t state;
        size_t res;

        memset( &state, 0, sizeof(state) );

        res = mbrtowc( &c, pos, end-pos, &state );

        if( res == (size_t)-1 )
        {
            pos++;
            continue;
        }
        else if( res == (size_t)-2 )
        {
            break;
        }
        else if( res == (size_t)0 )
        {
            pos++;
            continue;
        }
        pos += res;

        if( c == L'\n' )
        {
            if( timestamp_mode )
            {
                const wchar_t *time_string = out.c_str();
                while( *time_string && !iswdigit(*time_string))
                    time_string++;
                errno=0;

                if( *time_string )
                {
                    time_t tm;
                    wchar_t *end;

                    errno = 0;
                    tm = (time_t)wcstol( time_string, &end, 10 );

                    if( tm && !errno && !*end )
                    {
                        timestamp = tm;
                    }

                }

                out.clear();
                timestamp_mode = false;
                continue;
            }
            if( !was_backslash )
                break;
        }

        if( first_char )
        {
            if( c == L'#' )
                timestamp_mode = true;
        }

        first_char = false;

        out.push_back(c);

        was_backslash = ( (c == L'\\') && !was_backslash);

    }
    
    out = history_unescape_newlines_fish_1_x(out);
    return history_item_t(out, timestamp);
}