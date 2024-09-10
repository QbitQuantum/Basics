void StatusWidget::setStatusData( const Status &status )
{
    statusData = &status.entry;
    m_ui->favoriteReplyButton->disconnect();

    setDisplayMode( StatusModel::instance()->displayMode() );
    m_ui->userStatus->setHtml( statusData->text );
    m_ui->userImage->setPixmap( status.image );


    if ( statusData->type == Entry::Status ) {
        //adjust tooltip for reply/delete button
        if ( statusData->isOwn ) {
            m_ui->replyDeleteButton->setIcon( QIcon(":/icons/cross_16.png") );
            m_ui->replyDeleteButton->setToolTip( tr( "Delete status" ) );
        } else {
            m_ui->replyDeleteButton->setIcon( QIcon(":/icons/reply_16.png") );
            m_ui->replyDeleteButton->setToolTip( tr( "Reply to %1" ).arg( statusData->userInfo.screenName ) );
        }

        // favorite button
        if ( statusData->favorited ) {
            m_ui->favoriteReplyButton->setIcon( QIcon( ":/icons/star_on_16.png" ) );
            m_ui->favoriteReplyButton->setToolTip( tr( "Remove from Favorites" ) );
        } else {
            m_ui->favoriteReplyButton->setIcon( QIcon( ":/icons/star_off_16.png" ) );
            m_ui->favoriteReplyButton->setToolTip( tr( "Add to Favorites" ) );
        }
        connect( m_ui->favoriteReplyButton, SIGNAL(clicked()), this, SLOT(slotFavorite()) );

        // delete action
    } else {
        //adjust tooltip for reply/delete button and delete action
        m_ui->replyDeleteButton->setIcon( QIcon(":/icons/cross_16.png") );
        if ( currentServiceUrl == Account::NetworkUrlTwitter ) {
            m_ui->replyDeleteButton->setToolTip( tr( "Delete message" ) );
            m_ui->replyDeleteButton->setEnabled( true );
        } else {
            m_ui->replyDeleteButton->setToolTip( tr( "Deleting messages is not supported by StatusNet" ) );
            m_ui->replyDeleteButton->setEnabled( false );
        }

        // favorite button
        m_ui->favoriteReplyButton->setIcon( QIcon( ":/icons/reply_16.png" ) );
        m_ui->favoriteReplyButton->setToolTip( tr( "Reply to %1" ).arg( statusData->userInfo.screenName ) );
        connect( m_ui->favoriteReplyButton, SIGNAL(clicked()), this, SLOT(slotDM()) );

    }


    //display status's send time
    if( statusData->localTime.date() >= QDateTime::currentDateTime().date()) //today
        m_ui->timeStamp->setText( statusData->localTime.time().toString(Qt::SystemLocaleShortDate) );
    else  //yesterday or earlier
        m_ui->timeStamp->setText( statusData->localTime.toString(Qt::SystemLocaleShortDate) );

    //display in_reply_to link
    if( statusData->hasInReplyToStatusId ) {
        QString inReplyToUrl = currentServiceUrl;
        inReplyToUrl.remove( QRegExp("/api$", Qt::CaseInsensitive) );
        if ( currentServiceUrl == Account::NetworkUrlTwitter ) {
            inReplyToUrl.append( "/" + statusData->inReplyToScreenName + "/statuses/" + QString::number( statusData->inReplyToStatusId ) );
        }
        else {
            //for identica it works as is
            inReplyToUrl.append( "/notice/" + QString::number( statusData->inReplyToStatusId ) );
        }
        m_ui->timeStamp->setText( m_ui->timeStamp->text().append( " " )
                                  .append( tr( "in reply to %1" )
                                           .arg( QString( "<a style=\"color:rgb(255, 248, 140)\" href=%1>%2</a>" )
                                                 .arg( inReplyToUrl, statusData->inReplyToScreenName ) ) ) );
    }

    m_ui->infoButton->setData( &status );


    setState( status.state );
    setupMenu();
    adjustSize();
}