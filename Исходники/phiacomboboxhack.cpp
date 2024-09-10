void PHIAComboButton::setItems( const QStringList &list, int selected )
{
    if ( _popup ) delete _popup;
    _popup=new QMenu();
    QActionGroup *group=new QActionGroup( _popup );
    group->setExclusive( true );
    QList <QAction*> actions;
    for ( int i=0; i<list.count();i++ ) {
        QAction *action=new QAction( list.at( i ), 0 );
        action->setCheckable( true );
        action->setData( i );
        group->addAction( action );
        if ( i==selected ) action->setChecked( true );
        actions << action;
    }

    _popup->addActions( actions );
    _popup->setMinimumWidth( 100 );

    if ( actions.count() > selected ) setDefaultAction( actions.at( selected ) );

    setMenu( _popup );
    connect( _popup, SIGNAL( triggered( QAction* ) ), this,
        SIGNAL( selectedAction( QAction* ) ) );
}