KFindTextDialog::KFindTextDialog( QWidget *parent, const char *name )
    : QDialog( parent, name )
{
    // mimimise initial size of dialog
    resize( 0, 0 );

    QVBoxLayout *vl = new QVBoxLayout( this, 15 );

    QHBoxLayout *hl = new QHBoxLayout( 15 );
    vl->addLayout( hl );

    QLabel *label = new QLabel( i18n( "Find:" ), this );
    label->setFixedSize( label->sizeHint() );

    QLineEdit *edit = new QLineEdit( this );
    edit->setFixedHeight( edit->sizeHint().height() );
    edit->setFocus();
    connect( edit, SIGNAL( textChanged( const char * ) ),
		    SLOT( slotTextChanged( const char * ) ) );

    hl->addWidget( label );
    hl->addWidget( edit );

    hl = new QHBoxLayout;
    vl->addLayout( hl );

    QCheckBox *cb = new QCheckBox( i18n( "Case &sensitive" ), this );
    connect( cb, SIGNAL( toggled( bool ) ), this, SLOT( slotCase( bool ) ) );
    cb->setFixedSize( cb->sizeHint() );
    hl->addWidget( cb );

    hl->addStretch();

    hl = new QHBoxLayout( 15 );
    vl->addLayout( hl );

    QPushButton *btn = new QPushButton( i18n( "&Find" ), this );
    btn->setFixedSize( btn->sizeHint() );
    btn->setDefault( true );
    connect( btn, SIGNAL( clicked() ), this, SLOT( slotFind() ) );
    hl->addWidget( btn );

    hl->addStretch();

    btn = new QPushButton( i18n( "&Close" ), this );
    btn->setFixedSize( btn->sizeHint() );
    connect( btn, SIGNAL( clicked() ), this, SLOT( slotClose() ) );
    hl->addWidget( btn );

    vl->activate();

    rExp.setCaseSensitive( false );
}