void CreateAlias::execute()
{
    if ( !d->address ) {
        Utf8Codec c;
        parseOptions();
        d->address = nextAsAddress();
        EString * first = args()->firstElement();
        if ( first && !first->startsWith( "/" ) && first->contains( "@" ) )
            d->destination = nextAsAddress();
        else
            d->mailboxName = c.toUnicode( next() );
        end();

        if ( !c.valid() )
            error( "Argument encoding: " + c.error() );

        database( true );
        if ( !d->mailboxName.isEmpty() )
            Mailbox::setup( this );
    }

    if ( !choresDone() )
        return;

    if ( !d->t ) {
        if ( !d->mailboxName.isEmpty() ) {
            d->mailbox = Mailbox::obtain( d->mailboxName, false );
            if ( !d->mailbox || d->mailbox->deleted() )
                error( "No mailbox named " + d->mailboxName.utf8() );
        }

        d->t = new Transaction( this );
        List< Address > l;
        l.append( d->address );
        if ( d->destination )
            l.append( d->destination );
        AddressCreator * ac = new AddressCreator( &l, d->t );
        ac->execute();
    }

    if ( !d->address->id() || ( d->destination && !d->destination->id() ) )
        return;

    if ( !d->q ) {
        if ( d->destination ) {
            d->q = new Query( "insert into aliases (address, mailbox) "
                              "select $1, mailbox from aliases al "
                              "join addresses a on (al.address=a.id) "
                              "where a.localpart=$2"
                              " and a.domain=$3 "
                              "limit 1",
                              this );
            d->q->bind( 1, d->address->id() );
            d->q->bind( 2, d->destination->localpart() );
            d->q->bind( 3, d->destination->domain() );
        }
        else {
            d->q = new Query( "insert into aliases (address, mailbox) "
                              "values ($1, $2)", this );
            d->q->bind( 1, d->address->id() );
            d->q->bind( 2, d->mailbox->id() );
        }
        d->t->enqueue( d->q );
        d->t->execute();
    }

    if ( !d->q->done() )
        return;

    if ( d->q->failed() )
        error( "Couldn't create alias: " + d->q->error() );

    if ( d->q->rows() < 1 )
        error( "Could not locate destination for alias" );
    else if ( d->q->rows() > 1 )
        error( "Internal error: Inserted " + fn( d->q->rows() ) +
               " instead of 1. Not committing." );

    d->t->commit();

    finish();
}