bool ManageSieveCommand::explain()
{
    if ( !::x )
        ::x = new ExplainStuff;

    whitespace();
    while ( d->no.isEmpty() && d->pos < d->arg.length() ) {
        EString name = string();
        whitespace();
        EString value = string();
        whitespace();
        if ( name == "from" || name == "to" ) {
            if ( value.isEmpty() ) {
                if ( name == "from" )
                    ::x->from = 0;
                else
                    ::x->to = 0;
            }
            else {
                AddressParser ap( value );
                ap.assertSingleAddress();
                if ( ap.addresses()->count() != 1 )
                    no( "Need exactly one address for " + name );
                else if ( name == "from" )
                    ::x->from = ap.addresses()->first();
                else
                    ::x->to = ap.addresses()->first();
            }
        }
        else if ( name == "keep" ) {
            if ( value.isEmpty() ) {
                ::x->keep = 0;
            }
            else {
                Utf8Codec u;
                ::x->keep = Mailbox::find( u.toUnicode( value ) );
                if ( !::x->keep )
                    no( "No such mailbox: " + value );
            }
        }
        else if ( name == "script" ) {
            if ( value.isEmpty() ) {
                ::x->script = 0;
            }
            else {
                if ( !::x->script )
                    ::x->script = new SieveScript;
                ::x->script->parse( value );
                if ( ::x->script->isEmpty() )
                    no( "Script cannot be empty" );
                EString e = ::x->script->parseErrors();
                if ( !e.isEmpty() )
                    no( e );
            }
        }
        else if ( name == "message" ) {
            if ( value.isEmpty() ) {
                ::x->message = 0;
            }
            else {
                ::x->message = new Injectee;
                ::x->message->parse( value );
                ::x->message->setRfc822Size( ::x->message->rfc822().length() );
                if ( !::x->message->error().isEmpty() )
                    no( "Message parsing: " + ::x->message->error() );
            }
        }
        else {
            no( "Unknown name: " + name );
        }
    }

    if ( !::x->script )
        no( "No sieve (yet)" );
    if ( !::x->from )
        no( "No sender address (yet)" );
    if ( !::x->to )
        no( "No recipient address (yet)" );
    if ( !::x->keep )
        no( "No keep mailbox (yet)" );

    if ( !d->no.isEmpty() )
        return true;

    Sieve s;
    s.setSender( ::x->from );
    s.addRecipient( ::x->to, ::x->keep, d->sieve->user(), ::x->script );
    s.evaluate();
    uint a = s.actions( ::x->to )->count();
    bool m = false;
    if ( ::x->message && !s.done() ) {
        s.setMessage( ::x->message, new Date );
        s.evaluate();
        m = true;
    }
    if ( ::x->message && !m )
        d->sieve->send( "Script did not need the message" );
    else if ( !s.done() )
        d->sieve->send( "Script did not complete" );

    uint n = 0;
    List<SieveAction>::Iterator sa( s.actions( ::x->to ) );
    while ( sa ) {
        EString r( "Action: " );
        switch ( sa->type() ) {
        case SieveAction::Reject:
            r.append( "reject" );
            break;
        case SieveAction::FileInto:
            r.append( "fileinto " );
            r.append( sa->mailbox()->name().utf8() );
            break;
        case SieveAction::Redirect:
            r.append( "redirect " );
            r.append( sa->recipientAddress()->localpart() );
            r.append( "@" );
            r.append( sa->recipientAddress()->domain() );
            break;
        case SieveAction::MailtoNotification:
            r.append( "mailto notification to " );
            r.append( sa->recipientAddress()->lpdomain() );
            break;
        case SieveAction::Discard:
            r.append( "discard" );
            break;
        case SieveAction::Vacation:
            r.append( "send vacation message to " );
            r.append( sa->recipientAddress()->lpdomain() );
            r.append( " with subject " );
            r.append( sa->message()->header()->subject() );
            break;
        case SieveAction::Error:
            r = "Error: ";
            r.append( sa->errorMessage().simplified() );
            break;
        }
        if ( m && a && n<a )
            r.append( " (before seeing the message text)" );
        d->sieve->send( r );
        ++sa;
        n++;
    }

    return true;
}