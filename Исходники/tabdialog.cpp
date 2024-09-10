void TabDialog::setupTab1()
{
    QVBox *tab1 = new QVBox( this );
    tab1->setMargin( 5 );

    (void)new QLabel( "Filename:", tab1 );
    QLineEdit *fname = new QLineEdit( filename, tab1 );
    fname->setFocus();

    (void)new QLabel( "Path:", tab1 );
    QLabel *path = new QLabel( fileinfo.dirPath( TRUE ), tab1 );
    path->setFrameStyle( QFrame::Panel | QFrame::Sunken );

    (void)new QLabel( "Size:", tab1 );
    QLabel *size = new QLabel( QString( "%1 KB" ).arg( fileinfo.size() ), tab1 );
    size->setFrameStyle( QFrame::Panel | QFrame::Sunken );

    (void)new QLabel( "Last Read:", tab1 );
    QLabel *lread = new QLabel( fileinfo.lastRead().toString(), tab1 );
    lread->setFrameStyle( QFrame::Panel | QFrame::Sunken );

    (void)new QLabel( "Last Modified:", tab1 );
    QLabel *lmodif = new QLabel( fileinfo.lastModified().toString(), tab1 );
    lmodif->setFrameStyle( QFrame::Panel | QFrame::Sunken );

    addTab( tab1, "General" );
}