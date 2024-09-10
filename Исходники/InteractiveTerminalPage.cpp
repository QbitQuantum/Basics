void
InteractiveTerminalPage::onActivate()
{
    if ( m_termHostWidget )
        return;
    // For whatever reason, instead of simply linking against a library we
    // need to do a runtime query to KService just to get a sodding terminal
    // widget.
    KService::Ptr service = KService::serviceByDesktopName( "konsolepart" );
    if ( !service )
    {
        // And all of this hoping the Konsole application is installed. If not,
        // tough cookies.
        // Maybe linking against a library seemed too simple and elegant so
        // someone decided to have a terminal widget depend on over 9000 other
        // KDElibs things that have nothing to do with a terminal widget, and
        // have the loading happen at runtime so it's more likely to fail at
        // an inconvenient time.
        QMessageBox::critical( this,
                               tr( "Konsole not installed"),
                               tr( "Please install the kde konsole and try again!" ),
                               QMessageBox::Ok);
        return ;
    }

    // Create one instance of konsolepart.
    KParts::ReadOnlyPart* p =
        service->createInstance< KParts::ReadOnlyPart >( this,
                                                         this,
                                                         {} );
    if ( !p )
    {
        // One more opportunity for the loading operation to fail.
        QMessageBox::critical( this,
                               tr( "Konsole not installed"),
                               tr( "Please install the kde konsole and try again!" ),
                               QMessageBox::Ok);
        return;
    }

    // Cast the konsolepart to the TerminalInterface...
    TerminalInterface* t = qobject_cast< TerminalInterface* >( p );
    if ( !t )
    {
        // This is why we can't have nice things.
        QMessageBox::critical( this,
                               tr( "Konsole not installed"),
                               tr( "Please install the kde konsole and try again!" ),
                               QMessageBox::Ok);
        return;
    }

    // Make the widget persist even if the KPart goes out of scope...
    p->setAutoDeleteWidget( false );
    // ... but kill the KPart if the widget goes out of scope.
    p->setAutoDeletePart( true );

    m_termHostWidget = p->widget();
    m_layout->addWidget( m_termHostWidget );
    cDebug() << "Part widget ought to be"
             << m_termHostWidget->metaObject()->className();

    t->showShellInDir( QDir::home().path() );
    t->sendInput( QString( "%1\n" ).arg( m_command ) );
}