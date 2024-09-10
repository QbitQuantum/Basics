/**
 * First Panel - Meta Info
 * All the usual MetaData are displayed and can be changed.
 **/
MetaPanel::MetaPanel( QWidget *parent,
                      intf_thread_t *_p_intf )
                      : QWidget( parent ), p_intf( _p_intf )
{
    QGridLayout *metaLayout = new QGridLayout( this );
    metaLayout->setVerticalSpacing( 0 );

    QFont smallFont = QApplication::font();
    smallFont.setPointSize( smallFont.pointSize() - 1 );
    smallFont.setBold( true );

    int line = 0; /* Counter for GridLayout */
    p_input = NULL;
    QLabel *label;

#define ADD_META( string, widget, col, colspan ) {                        \
    label = new QLabel( qtr( string ) ); label->setFont( smallFont );     \
    label->setContentsMargins( 3, 2, 0, 0 );                              \
    metaLayout->addWidget( label, line++, col, 1, colspan );              \
    widget = new QLineEdit;                                               \
    metaLayout->addWidget( widget, line, col, 1, colspan );               \
    CONNECT( widget, textEdited( QString ), this, enterEditMode() );      \
}

    /* Title, artist and album*/
    ADD_META( VLC_META_TITLE, title_text, 0, 10 ); line++;
    ADD_META( VLC_META_ARTIST, artist_text, 0, 10 ); line++;
    ADD_META( VLC_META_ALBUM, collection_text, 0, 7 );

    /* Date */
    label = new QLabel( qtr( VLC_META_DATE ) );
    label->setFont( smallFont ); label->setContentsMargins( 3, 2, 0, 0 );
    metaLayout->addWidget( label, line - 1, 7, 1, 2 );

    /* Date (Should be in years) */
    date_text = new QLineEdit;
    date_text->setAlignment( Qt::AlignRight );
    date_text->setInputMask("0000");
    date_text->setMaximumWidth( 128 );
    metaLayout->addWidget( date_text, line, 7, 1, -1 );
    line++;

    /* Genre Name */
    /* TODO List id3genres.h is not includable yet ? */
    ADD_META( VLC_META_GENRE, genre_text, 0, 7 );

    /* Number - on the same line */
    label = new QLabel( qtr( VLC_META_TRACK_NUMBER ) );
    label->setFont( smallFont ); label->setContentsMargins( 3, 2, 0, 0 );
    metaLayout->addWidget( label, line - 1, 7, 1, 3  );

    tracknumber_text = new QLineEdit;
    tracknumber_text->setAlignment( Qt::AlignRight );
    tracknumber_text->setInputMask("0000/0000");
    tracknumber_text->setMaximumWidth( 128 );
    metaLayout->addWidget( tracknumber_text, line, 7, 1, -1 );

    line++;

    /* Rating - on the same line */
    /*
    metaLayout->addWidget( new QLabel( qtr( VLC_META_RATING ) ), line, 4, 1, 2 );
    rating_text = new QSpinBox; setSpinBounds( rating_text );
    metaLayout->addWidget( rating_text, line, 6, 1, 1 );
    */

    /* Now Playing - Useful for live feeds (HTTP, DVB, ETC...) */
    ADD_META( VLC_META_NOW_PLAYING, nowplaying_text, 0, 7 );
    nowplaying_text->setReadOnly( true ); line--;

    /* Language on the same line */
    ADD_META( VLC_META_LANGUAGE, language_text, 7, -1 ); line++;
    ADD_META( VLC_META_PUBLISHER, publisher_text, 0, 7 ); line++;

    lblURL = new QLabel;
    lblURL->setOpenExternalLinks( true );
    lblURL->setTextFormat( Qt::RichText );
    metaLayout->addWidget( lblURL, line -1, 7, 1, -1 );

    ADD_META( VLC_META_COPYRIGHT, copyright_text, 0,  7 ); line++;

    /* ART_URL */
    art_cover = new CoverArtLabel( this, p_intf );
    metaLayout->addWidget( art_cover, line, 7, 6, 3, Qt::AlignLeft );

    ADD_META( VLC_META_ENCODED_BY, encodedby_text, 0, 7 ); line++;

    label = new QLabel( qtr( N_("Comments") ) ); label->setFont( smallFont );
    label->setContentsMargins( 3, 2, 0, 0 );
    metaLayout->addWidget( label, line++, 0, 1, 7 );
    description_text = new QTextEdit;
    description_text->setAcceptRichText( false );
    metaLayout->addWidget( description_text, line, 0, 1, 7 );
    // CONNECT( description_text, textChanged(), this, enterEditMode() ); //FIXME
    line++;

    /* VLC_META_SETTING: Useless */
    /* ADD_META( TRACKID )  Useless ? */
    /* ADD_URI - Do not show it, done outside */

    metaLayout->setColumnStretch( 1, 20 );
    metaLayout->setColumnMinimumWidth ( 1, 80 );
    metaLayout->setRowStretch( line, 10 );
#undef ADD_META

    CONNECT( tracknumber_text, textEdited( QString ), this, enterEditMode() );

    CONNECT( date_text, textEdited( QString ), this, enterEditMode() );
//    CONNECT( THEMIM->getIM(), artChanged( QString ), this, enterEditMode() );
/*    CONNECT( rating_text, valueChanged( QString ), this, enterEditMode( QString ) );*/

    /* We are not yet in Edit Mode */
    b_inEditMode = false;
}