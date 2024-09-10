QAction *MenuBarManager::addMenu( const QString & name , QMenu *menu )
{
    QAction *action = new QAction( name , this );
        action->setMenu( menu );

    this->addAction( action );

    return action;
}