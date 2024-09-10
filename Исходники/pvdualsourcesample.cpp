void PvDualSourceSample::CreateLayout()
{
    CreateMenu();

    mSource1 = new Source( 0 );
    mSource1Widget = new SourceWidget( "Source 1", mSource1 );
    mSource1->SetWidget( mSource1Widget );

    mSource2 = new Source( 1 );
    mSource2Widget = new SourceWidget( "Source 2", mSource2 );
    mSource2->SetWidget( mSource2Widget );

    QHBoxLayout *lLayout = new QHBoxLayout;
    lLayout->addWidget( mSource1Widget );
    lLayout->addWidget( mSource2Widget );

    QFrame *lMainBox = new QFrame;
    lMainBox->setLayout( lLayout );

    setCentralWidget( lMainBox );
    setWindowTitle( tr( "PvDualSourceSample" ) );
    setWindowIcon( QIcon( QPixmap( ":PvDualSourceSample/res/PvDualSourceSample.ico" ) ) );

    EnableInterface();
}