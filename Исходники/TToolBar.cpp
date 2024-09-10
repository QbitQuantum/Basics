void TToolBar::addButton( TFlipButton * pB )
{
    if( ! mpTAction->mUseCustomLayout )
    {
        QSize size = pB->minimumSizeHint();
        if( pB->mpTAction->getButtonRotation() > 0 )
        {
            size.transpose();
        }
        pB->setMaximumSize( size );
        pB->setMinimumSize( size );
    }
    else
    {
        QSize size = QSize(pB->mpTAction->mSizeX, pB->mpTAction->mSizeY );
        pB->setMaximumSize( size );
        pB->setMinimumSize( size );
        pB->setParent( mpWidget );
        pB->setGeometry( pB->mpTAction->mPosX, pB->mpTAction->mPosY, pB->mpTAction->mSizeX, pB->mpTAction->mSizeY );
    }

    pB->setStyleSheet( pB->mpTAction->css );
    pB->setFlat( pB->mpTAction->getButtonFlat() );
    int rotation = pB->mpTAction->getButtonRotation();
    switch( rotation )
    {
        case 0: pB->setOrientation( Qt::Horizontal ); break;
        case 1: pB->setOrientation( Qt::Vertical ); break;
        case 2: pB->setOrientation( Qt::Vertical ); pB->setMirrored( true ); break;
    }

    if( ! mpTAction->mUseCustomLayout )
    {
        // tool bar mButtonColumns > 0 -> autolayout
        // case == 0: use individual button placment for user defined layouts
        int columns = mpTAction->getButtonColumns();
        if( columns <= 0 ) columns = 1;
        if( columns > 0 )
        {
            mItemCount++;
            int row = mItemCount / columns;
            int col = mItemCount % columns;
            if( mVerticalOrientation )
            {
                mpLayout->addWidget( pB, row, col );
            }
            else
            {
                mpLayout->addWidget( pB, col, row );
            }
        }
    }
    else
    {
        pB->move( pB->mpTAction->mPosX, pB->mpTAction->mPosY );
    }
    connect( pB, SIGNAL(pressed()), this, SLOT(slot_pressed()) );
}