int main( int argc, char *argv[] )
{
    Scope global;

    EString sender;
    UString mailbox;
    EString recipient;
    EString filename;
    int verbose = 0;
    bool error = false;

    int n = 1;
    while ( n < argc ) {
        if ( argv[n][0] == '-' ) {
            switch ( argv[n][1] ) {
            case 'f':
                if ( argc - n > 1 )
                    sender = argv[++n];
                break;

            case 't':
                if ( argc - n > 1 ) {
                    Utf8Codec c;
                    mailbox = c.toUnicode( argv[++n] );
                    if ( !c.valid() )
                        error = true;
                }
                break;

            case 'v':
                {
                    int i = 1;
                    while ( argv[n][i] == 'v' ) {
                        verbose++;
                        i++;
                    }
                    if ( argv[n][i] != '\0' )
                        error = true;
                }
                break;

            default:
                error = true;
                break;
            }
        }
        else if ( recipient.isEmpty() ) {
            recipient = argv[n];
        }
        else if ( filename.isEmpty() ) {
            filename = argv[n];
        }
        else {
            error = true;
        }
        n++;
    }

    if ( error || recipient.isEmpty() ) {
        fprintf( stderr,
                 "Syntax: deliver [-v] [-f sender] recipient [filename]\n" );
        exit( -1 );
    }

    EString contents;
    if ( filename.isEmpty() ) {
        char s[128];
        while ( fgets( s, 128, stdin ) != 0 )
            contents.append( s );
    }
    else {
        File message( filename );
        if ( !message.valid() ) {
            fprintf( stderr, "Unable to open message file %s\n",
                     filename.cstr() );
            exit( -1 );
        }
        contents = message.contents();
    }

    Configuration::setup( "archiveopteryx.conf" );

    Injectee * message = new Injectee;
    message->parse( contents );
    if ( !message->error().isEmpty() ) {
        fprintf( stderr,
                 "Message parsing failed: %s", message->error().cstr( ) );
        exit( EX_DATAERR );
    }

    if ( verbose > 0 )
        fprintf( stderr, "Sending to <%s>\n", recipient.cstr() );

    EventLoop::setup();
    Database::setup( 1 );
    Log * l = new Log;
    Allocator::addEternal( l, "delivery log" );
    global.setLog( l );
    Allocator::addEternal( new StderrLogger( "deliver", verbose ),
                           "log object" );

    Configuration::report();
    Mailbox::setup();
    Deliverator * d = new Deliverator( message, mailbox, recipient );
    EventLoop::global()->start();
    if ( !d->i || d->i->failed() )
        return EX_UNAVAILABLE;

    if ( verbose )
        fprintf( stderr,
                 "deliver: Stored in %s as UID %d\n",
                 d->mb->name().utf8().cstr(),
                 d->m->uid( d->mb ) );
    return 0;
}