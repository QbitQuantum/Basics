void ImapUrl::parse( const EString & s )
{
    d->orig = s;
    ImapUrlParser * p = new ImapUrlParser( s );

    // imapurl = "imap://" iserver "/" icommand

    if ( !d->imap ) {
        if ( !p->present( "imap://" ) )
            return;

        // iserver = [ iuserauth "@" ] hostport
        // iuserauth = enc_user [iauth] / [enc_user] iauth

        if ( p->hasIuserauth() ) {
            d->user = new User;
            Utf8Codec c;
            d->user->setLogin( c.toUnicode( p->xchars() ) );
            if ( !c.valid() )
                return;
            if ( p->present( ";AUTH=" ) )
                d->auth = p->xchars();
            else if ( d->user->login().isEmpty() )
                return;
            if ( !p->present( "@" ) )
                return;
        }

        if ( !p->hostport( d->host, &d->port ) )
            return;
    }

    // icommand = enc_mailbox [uidvalidity] iuid [isection]

    if ( !( d->imap && d->imap->session() ) || !p->hasUid() ) {
        if ( !p->present( "/" ) )
            return;

        Utf8Codec c;
        d->mailbox = c.toUnicode( p->xchars( true ) );
        if ( d->mailbox.isEmpty() )
            return;
        if( !c.valid() )
            return;

        if ( p->present( ";uidvalidity=" ) ) {
            d->uidvalidity = p->nzNumber();
            if ( !p->ok() )
                return;
        }
    }

    p->require( "/;uid=" );
    d->uid = p->number();

    if ( p->present( "/;section=" ) )
        d->section = p->xchars( true );

    // RFC 4467 additions:
    // [ ";EXPIRE=" date-time ] ";URLAUTH=" access ":" mechanism ":" urlauth
    // (These clauses apply only to absolute URLs.)

    if ( !d->imap ) {
        if ( p->nextChar() == ';' ) {
            if ( p->present( ";expire=" ) )
                d->expires = p->isoTimestamp();
            p->require( ";urlauth=" );
            if ( p->present( "submit+" ) )
                d->access = "submit+" + p->xchars();
            else if ( p->present( "user+" ) )
                d->access = "user+" + p->xchars();
            else if ( p->present( "authuser" ) )
                d->access = "authuser";
            else if ( p->present( "anonymous" ) )
                d->access = "anonymous";
            else
                return;
            d->rumpEnd = p->pos();
            if ( p->present( ":" ) ) {
                p->require( "internal" );
                p->require( ":" );
                d->urlauth = p->urlauth();
                d->mechanism = "internal";
            }
            else {
                d->isRump = true;
            }
        }
    }

    p->end();
    if ( !p->ok() )
        return;

    d->valid = true;
}