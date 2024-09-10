void SieveTest::parse()
{
    if ( identifier() == "address" ) {
        findComparator();
        findMatchType();
        findAddressPart();
        arguments()->numberRemainingArguments();
        d->headers = takeHeaderFieldList( 1 );
        d->keys = arguments()->takeStringList( 2 );
    }
    else if ( identifier() == "allof" ||
              identifier() == "anyof" ) {
        if ( !arguments()->arguments()->isEmpty() )
            setError( "Test '" +
                      identifier() +
                      "' does not accept arguments, only a list of tests" );
        bool any = false;
        List<SieveTest>::Iterator i( arguments()->tests() );
        while ( i ) {
            any = true;
            i->parse();
            if ( i->ihaveFailed() )
                setIhaveFailed();
            addExtensions( i->addedExtensions() );
            ++i;
        }
        if ( !any )
            setError( "Need at least one subsidiary test" );
    }
    else if ( identifier() == "envelope" ) {
        require( "envelope" );
        findComparator();
        findMatchType();
        findAddressPart();
        arguments()->numberRemainingArguments();
        d->envelopeParts = arguments()->takeStringList( 1 );
        d->keys = arguments()->takeStringList( 2 );
        UStringList::Iterator i( d->envelopeParts );
        while ( i ) {
            EString s = i->utf8().lower();
            if ( s == "from" || s == "to" ) {
                Utf8Codec c;
                *i = c.toUnicode( s );
            }
            // else if and blah for extensions - extensions are only
            // valid after the right require
            else {
                // better if we could setError on the right item, but it's gone
                setError( "Unsupported envelope part: " + i->utf8() );
            }
            ++i;
        }
    }
    else if ( identifier() == "exists" ) {
        arguments()->numberRemainingArguments();
        d->headers = takeHeaderFieldList( 1 );
    }
    else if ( identifier() == "false" ) {
        // I wish all the tests were this easy
    }
    else if ( identifier() == "header" ) {
        findComparator();
        findMatchType();
        arguments()->numberRemainingArguments();
        d->headers = takeHeaderFieldList( 1 );
        d->keys = arguments()->takeStringList( 2 );
    }
    else if ( identifier() == "date" ||
              identifier() == "currentdate" )
    {
        require( "date" );
        findComparator();
        findMatchType();

        d->zone = arguments()->takeTaggedString( ":zone" );
        if ( d->zone.isEmpty() &&
             arguments()->findTag( ":originalzone" ) )
            d->zone.append( "-0000" );

        arguments()->numberRemainingArguments();

        uint n = 1;

        if ( identifier() == "date" ) {
            d->headers = takeHeaderFieldList( n++ );
            if ( d->headers && d->headers->count() != 1 )
                setError( "Only one date field may be specified" );
        }

        d->datePart = arguments()->takeString( n++ );
        d->keys = arguments()->takeStringList( n );
    }
    else if ( identifier() == "not" ) {
        if ( !arguments()->arguments()->isEmpty() )
            setError( "Test 'not' does not accept arguments, only a test" );
        if ( !arguments()->tests() ||
             arguments()->tests()->count() != 1 )
            setError( "Test 'not' needs exactly one subsidiary test" );
        else
            arguments()->tests()->first()->parse();
    }
    else if ( identifier() == "size" ) {
        arguments()->allowOneTag( ":over", ":under" );
        if ( arguments()->findTag( ":over" ) ) {
            d->sizeOver = true;
            d->sizeLimit = arguments()->takeTaggedNumber( ":over" );
        }
        else if ( arguments()->findTag( ":under" ) ) {
            d->sizeOver = false;
            d->sizeLimit = arguments()->takeTaggedNumber( ":under" );
        }
    }
    else if ( identifier() == "true" ) {
        // much like false.
    }
    else if ( identifier() == "body" ) {
        require( "body" );
        findComparator();
        findMatchType();
        arguments()->allowOneTag( ":raw", ":text", ":content" );
        if ( arguments()->findTag( ":raw" ) ) {
            d->bodyMatchType = Rfc822;
        }
        else if ( arguments()->findTag( ":text" ) ) {
            d->bodyMatchType = Text;
        }
        else if ( arguments()->findTag( ":content" ) ) {
            d->bodyMatchType = SpecifiedTypes;
            d->contentTypes = arguments()->takeTaggedStringList( ":content" );
        }
        arguments()->numberRemainingArguments();
        d->keys = arguments()->takeStringList( 1 );
    }
    else if ( identifier() == "ihave" ) {
        require( "ihave" );
        arguments()->numberRemainingArguments();
        arguments()->takeStringList( 1 );
    }
    else if ( identifier() == "valid_notify_method" ) {
        require( "enotify" );
        arguments()->numberRemainingArguments();
        UStringList * urls = arguments()->takeStringList( 1 );
        if ( !urls || urls->isEmpty() )
            setError( "No URLs" );
    }
    else if ( identifier() == "notify_method_capability" ) {
        require( "enotify" );
        findComparator();
        findMatchType();
        arguments()->numberRemainingArguments();
        (void)new SieveNotifyMethod( arguments()->takeString( 1 ),
                                     arguments()->takeArgument( 1 ),
                                     this );
        (void)arguments()->takeString( 2 ).utf8().lower();
        d->keys = arguments()->takeStringList( 3 );
    }
    else {
        setError( "Unknown test: " + identifier() );
    }

    if ( arguments() )
        arguments()->flagUnparsedAsBad();

    // if the ihave was correctly parsed and names something we don't
    // support, then we have to suppress some errors.
    if ( identifier() == "ihave" && error().isEmpty() ) {
        UStringList::Iterator i( arguments()->takeStringList( 1 ) );
        EStringList x;
        while ( i && supportedExtensions()->contains( i->ascii() ) ) {
            x.append( i->ascii() );
            ++i;
        }

        if ( i )
            setIhaveFailed();
        else
            addExtensions( &x );
    }
}