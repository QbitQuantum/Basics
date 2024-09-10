void FirstRun::buildPrivDialog()
{
    setWindowTitle( qtr( "Privacy and Network Access Policy" ) );
    setWindowRole( "vlc-privacy" );
    setWindowModality( Qt::ApplicationModal );
    setWindowFlags( Qt::Dialog );
    setAttribute( Qt::WA_DeleteOnClose );

    QGridLayout *gLayout = new QGridLayout( this );

    QGroupBox *blabla = new QGroupBox( qtr( "Privacy and Network Access Policy" ) );
    QGridLayout *blablaLayout = new QGridLayout( blabla );
    QLabel *text = new QLabel( qtr(
        "<p><i>VLC media player</i> does <b>not</b> send or collect any "
        "information, even anonymously, about your usage.</p>\n"
        "<p>However, it can connect to the Internet "
        "in order to display <b>medias information</b> "
#ifdef UPDATE_CHECK
        "or to check for available <b>updates</b>"
#endif
        ".</p>\n"
        "<p><i>VideoLAN</i> (the authors) requires you to express your consent "
        "before allowing this software to access the Internet.</p>\n"
        "<p>According to your choices, please check or uncheck the following options:</p>\n"
        ) );
    text->setWordWrap( true );
    text->setTextFormat( Qt::RichText );

    blablaLayout->addWidget( text, 0, 0 ) ;

    QGroupBox *options = new QGroupBox( qtr( "Network Access Policy" ) );
    QGridLayout *optionsLayout = new QGridLayout( options );

    gLayout->addWidget( blabla, 0, 0, 1, 3 );
    gLayout->addWidget( options, 1, 0, 1, 3 );
    int line = 0;

    checkbox = new QCheckBox( qtr( "Allow downloading media information" ) );
    checkbox->setChecked( true );
    optionsLayout->addWidget( checkbox, line++, 0 );

#ifdef UPDATE_CHECK
    checkbox2 = new QCheckBox( qtr( "Allow checking for VLC updates" ) );
    checkbox2->setChecked( true );
    optionsLayout->addWidget( checkbox2, line++, 0 );
#endif

    QDialogButtonBox *buttonsBox = new QDialogButtonBox( this );
    buttonsBox->addButton( qtr( "Save and Continue" ), QDialogButtonBox::AcceptRole );

    gLayout->addWidget( buttonsBox, 2, 0, 2, 3 );

    CONNECT( buttonsBox, accepted(), this, save() );
    buttonsBox->setFocus();
}