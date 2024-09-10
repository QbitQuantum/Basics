static int rcp_get_token(struct rcp_parser *parser)
{
    char tok = ' ';
    char *ptr;
    size_t ptr_len;

    while (isspace(tok))
        tok = GETCHAR(parser);

    ptr = parser->rcpp_str_buffer;

    /* tok can't be ipv4 */
    if (isalnum(tok)) {
        int xdigit, digit, dot_number;
        RT_ZERO(parser->rcpp_str_buffer);

        dot_number = 0;
        xdigit = 1;
        digit = 1;
        do {
            *ptr++ = tok;
            tok = GETCHAR(parser);

            if (!isalnum(tok) && tok != ':' && tok != '.' && tok != '-' && tok != '_')
                break;

            /**
             * if before ':' there were only [0-9][a-f][A-F],
             * then it can't be option.
             */
            xdigit &= (isxdigit(tok) || (tok == ':'));
            /**
             * We want hint to differ ipv4 and network name.
             */
            digit &= (isdigit(tok) || (tok == '.'));

            if (tok == ':')
            {
                if (xdigit == 1)
                {
                    int port = 0;
                    do
                    {
                        *ptr++ = tok;
                        tok = GETCHAR(parser);

                        if (tok == '.')
                            port++;

                    } while(PARSER_STOP(tok, parser, ptr) && (tok == ':' || tok == '.' || isxdigit(tok)));

                    PARSER_BUFFER_EXCEEDED(parser, ptr);

                    if (port == 0)
                        return tok_ipv6;
                    else if (port == 1)
                        return tok_ipv6_port;
                    else
                    {
                        /* eats rest of the token */
                        do
                        {
                            *ptr++ = tok;
                            tok = GETCHAR(parser);
                        } while(   PARSER_STOP(tok, parser, ptr)
                                && (isalnum(tok) || tok == '.'  || tok == '_' || tok == '-'));

                        PARSER_BUFFER_EXCEEDED(parser, ptr);

                        return tok_string;
                    }
                }
                else {
                    /* XXX: need further experiments */
                    return tok_option; /* option with value */
                }
            }

            if (tok == '.')
            {
                do {
                    if (tok == '.') dot_number++;

                    *ptr++ = tok;
                    digit &= (isdigit(tok) || (tok == '.'));
                    tok = GETCHAR(parser);
                } while(   PARSER_STOP(tok, parser, ptr)
                        && (isalnum(tok) || tok == '.' || tok == '_' || tok == '-'));

                PARSER_BUFFER_EXCEEDED(parser, ptr);

                if (dot_number == 3 && digit)
                    return tok_ipv4;
                else if (dot_number == 4 && digit)
                    return tok_ipv4_port;
                else
                    return tok_string;
            }
        } while(   PARSER_STOP(tok, parser, ptr)
                && (isalnum(tok) || tok == ':' || tok == '.' || tok == '-' || tok == '_'));

        PARSER_BUFFER_EXCEEDED(parser, ptr);

        if (digit || xdigit)
            return tok_number;
        if (RTStrCmp(parser->rcpp_str_buffer, "nameserver") == 0)
            return tok_nameserver;
        if (RTStrCmp(parser->rcpp_str_buffer, "port") == 0)
            return tok_port;
        if (RTStrCmp(parser->rcpp_str_buffer, "domain") == 0)
            return tok_domain;
        if (RTStrCmp(parser->rcpp_str_buffer, "search") == 0)
            return tok_search;
        if (RTStrCmp(parser->rcpp_str_buffer, "search_order") == 0)
            return tok_search_order;
        if (RTStrCmp(parser->rcpp_str_buffer, "sortlist") == 0)
            return tok_sortlist;
        if (RTStrCmp(parser->rcpp_str_buffer, "timeout") == 0)
            return tok_timeout;
        if (RTStrCmp(parser->rcpp_str_buffer, "options") == 0)
            return tok_options;

        return tok_string;
    }

    if (tok == EOF) return tok_eof;

    if (tok == '#')
    {
        do{
            tok = GETCHAR(parser);
        } while (tok != EOF && tok != '\r' && tok != '\n');

        if (tok == EOF) return tok_eof;

        return tok_comment;
    }
    return tok;
}