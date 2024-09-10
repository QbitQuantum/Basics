void
doYahooStep1(
        char       *buffer,
        const char *target,
        const char *username,
        const char *password,
        char       *cookie,
        size_t     *cookieSize
    )
{
    char    *request;
    char    *p, *q;
    char    src[MAX_NAMELEN];
    char    done[MAX_WEBPAGENAME];
    char    challenge[MAX_KEYLENGTH];
    char    u[MAX_USERIDLEN];
    char    passwd[BUFSIZ * 2];
    char    url[BUFSIZ * 2];
    int     tries     = 1;
    BOOL    escapeURL = TRUE;

    dputs( "doYahooStep1(): 実行開始\n" );

    // Yahoo! Japan にログイン
    request  = (char *)malloc( RCV_BUFFER_SIZE );
    if ( !request ) 
        return;

    src[0]       = NUL;
    done[0]      = NUL;
    challenge[0] = NUL;
    u[0]         = NUL;
    passwd[0]    = NUL;

    p = strstr( buffer, "name=\".tries\" value=\"" );
    if ( p ) {
        p += 21;
        q = strchr( p, '"' );
        if ( q ) {
            char    buf[BUFSIZ];

            strncpy( buf, p, q - p );
            buf[q - p] = NUL;
            tries = atol( buf );
        }
    }

    p = strstr( buffer, "name=\".src\" value=\"" );
    if ( p ) {
        p += 19;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( src, p, q - p );
            src[q - p] = NUL;
        }
    }
    p = strstr( buffer, "name=\".done\" value=\"" );
    if ( p ) {
        p += 20;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( done, p, q - p );
            done[q - p] = NUL;
        }
    }
    p = strstr( buffer, "name=\".challenge\" value=\"" );
    if ( p ) {
        p += 25;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( challenge, p, q - p );
            challenge[q - p] = NUL;
        }
    }
    p = strstr( buffer, "name=\".u\" value=\"" );
    if ( p ) {
        p += 17;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( u, p, q - p );
            u[q - p] = NUL;
        }
    }

    sprintf( passwd, "%s%s", ToLower(MD5(password)), challenge );
    strcpy( passwd, ToLower( MD5( passwd ) ) );

    strcpy( done, translateURL( done ) );
    p = strstr( done, "appdata" );
    if ( p ) {
        char    *r;
        p += 7;
        while ( ((q = strstr( p, "%3A" )) != NULL) ||
                ((q = strstr( p, "%2F" )) != NULL) ||
                ((q = strstr( p, "%2E" )) != NULL)    ) {
            r = p + strlen( p );
            while ( r > q ) {
                *(r + 2) = *r;
                r--;
            }
            *++q = '2';
            *++q = '5';
        }
    }

    strcpy( url, "http://login.yahoo.co.jp/config/login?" );
    sprintf( request,
             ".tries=%d&"
             ".src=%s&"
             ".md5=&"
             ".hash=&"
             ".js=1&"
             ".last=&"
             "promo=&"
             ".intl=jp&"
             ".bypass=&"
             ".partner=&"
             ".u=%s&"
             ".v=0&"
             ".challenge=%s&"
             ".yplus=&"
             ".emailCode=&"
             "pkg=&"
             "stepid=&"
             ".ev=&"
             "hasMsgr=0&"
             ".chkP=Y&"
             ".done=%s&"
             ".pd=&"
             ".protoctl=&"
             "login=%s&"
             "passwd=%s&"
             ".persistent=y&"
             ".hash=1&"
             ".md5=1",
             tries,
             src,
             u,
             challenge,
             done,
             username,
             passwd );
    strcat( url, request );

    if ( !strcmp( src, "ba_newsing" ) )
        escapeURL = FALSE;

    _httpGetIC( url, buffer, FALSE, escapeURL );
    if ( *buffer )
        doYahooStep1a( buffer, request, target,
                       username, password, cookie, cookieSize );

    free( request );
}