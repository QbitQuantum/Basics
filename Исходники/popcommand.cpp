bool PopCommand::user()
{
    if ( !d->user ) {
        log( "USER Command" );
        if ( !d->pop->accessPermitted() ) {
            d->pop->err( "Must enable TLS before login" );
            return true;
        }
        d->user = new ::User;
        Utf8Codec c;
        d->user->setLogin( c.toUnicode( nextArg() ) );
        d->pop->setUser( d->user, "POP3 login" );
        if ( c.valid() ) {
            d->user->refresh( this );
        }
        else {
            d->pop->err( "Argument encoding error: " + c.error() );
            d->pop->badUser();
            return true;
        }
    }

    if ( d->user->state() == User::Unverified )
        return false;

    if ( d->user->state() == User::Nonexistent ) {
        d->pop->err( "No such user" );
        d->pop->badUser();
    }
    else {
        d->pop->ok( "Done" );
    }

    return true;
}