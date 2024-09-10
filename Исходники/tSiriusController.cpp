//-----------------------------------------------------------------------------
//! All channel status popup
//-----------------------------------------------------------------------------
void tSiriusController::AllChannelStatus()
{
    const QList<tChannelInfo *>& chanList = m_rSiriusConnector.AllChannelList();

    if ( chanList.isEmpty() )
    {
//        Assert(chanList.size() > 0); // Must be at least the currently playing channel
        tMessageBox::Error( 0, tr( "All" ), tr( "No channels" ), tMessageBox::CLOSE );
        return;
    }

    m_pAllChannelStatusDialog = new tListenDialog( tr("Channels") + QString(" - ") + tr("All"), 0, true);
    m_pAllChannelStatusDialog->SetAlignment(tDialog::AlignScreenCenter);

    m_pAllChannelStatusTable = new tAllChannelStatus(m_pAllChannelStatusDialog);

    Connect(m_pAllChannelStatusTable, SIGNAL(Cancel()), m_pAllChannelStatusDialog, SLOT(reject()));
    Connect(m_pAllChannelStatusTable, SIGNAL(activated(const QModelIndex&)), 
        this, SLOT(TuneToHighlightedChannelFromAllChannelStatusTable()));

    Connect(m_pAllChannelStatusDialog, SIGNAL(accepted()), this, SLOT(TuneToHighlightedChannelAndAcceptFromAllChannelStatusTable()));
    Connect(this, SIGNAL(FavoriteUpdated(const bool)), m_pAllChannelStatusDialog, SLOT(OnFavoriteUpdated(const bool)));
    Connect(m_pAllChannelStatusTable, SIGNAL(NewFocusRow(const int)), this, SLOT(OnNewFocusRow(const int)));

    Connect(m_pAllChannelStatusDialog, SIGNAL(ToggleFavoriteMenuSelected()), m_pAllChannelStatusTable, SLOT(ToggleFavorite()));

    Connect(m_pAllChannelStatusDialog, SIGNAL(WheelIndicatesScrollUp()), m_pAllChannelStatusTable, SLOT(OnWheelIndicatesScrollUp()));
    Connect(m_pAllChannelStatusDialog, SIGNAL(WheelIndicatesScrollDown()), m_pAllChannelStatusTable, SLOT(OnWheelIndicatesScrollDown()));

    // Layout
    QVBoxLayout* pLayout = new QVBoxLayout;
    pLayout->addWidget(m_pAllChannelStatusTable);

    m_pAllChannelStatusDialog->setLayout(pLayout);
    m_pAllChannelStatusTable->SetRecords(chanList, m_ChannelId);

    Connect(m_pAllChannelStatusTable, SIGNAL(RowLocationPossiblyChanged(const QRect)), m_pAllChannelStatusDialog, SLOT(OnRowLocationPossiblyChanged(const QRect)));

    m_pAllChannelStatusDialog->exec();

    delete m_pAllChannelStatusDialog;
    m_pAllChannelStatusDialog = 0;
    //delete m_pAllChannelStatusTable;  we do not need to do this, it is owned by the dialog
    m_pAllChannelStatusTable = 0;
}