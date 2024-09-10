void TAction::insertActions( mudlet * pMainWindow, TToolBar * pT, QMenu * menu )
{
    mpToolBar = pT;
    QIcon icon( mIcon );
    EAction * action = new EAction( icon, mName, pMainWindow );
    action->setCheckable( mIsPushDownButton );
    action->mID = mID;
    action->mpHost = mpHost;
    action->setStatusTip( mName );
    menu->addAction( action );
    //mudlet::self()->bindMenu( menu, action );


    if( mIsFolder )
    {
        QMenu * newMenu = new QMenu( pMainWindow );
        newMenu->setStyleSheet( css );
        action->setMenu( newMenu );

        typedef list<TAction *>::const_iterator I;
        for( I it = mpMyChildrenList->begin(); it != mpMyChildrenList->end(); it++)
        {
            TAction * pChild = *it;
            pChild->insertActions( pMainWindow, pT, newMenu );
        }
    }
}