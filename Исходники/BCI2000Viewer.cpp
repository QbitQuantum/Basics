void
BCI2000Viewer::FillChannelList()
{
  ui->channelList->blockSignals( true );
  ui->channelList->clear();
  if( mFile.IsOpen() )
  {
    QListWidgetItem* pItem = new QListWidgetItem( tr("States"), ui->channelList );
    pItem->setBackground( cHeadingColor );
    pItem->setFlags( Qt::NoItemFlags );
    const StateList* states = mFile.States();
    for( int i = 0; i < states->Size(); ++i )
    {
      pItem = new QListWidgetItem( ( *states )[ i ].Name().c_str(), ui->channelList );
      pItem->setFlags( Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    }

    pItem = new QListWidgetItem( tr("Channels"), ui->channelList );
    pItem->setBackground( cHeadingColor );
    pItem->setFlags( Qt::NoItemFlags );
    int base = ui->channelList->count(),
        channelsInFile = mFile.SignalProperties().Channels();
    if( mFile.Parameters()->Exists( "ChannelNames" ) )
    {
      ParamRef ChannelNames = mFile.Parameter( "ChannelNames" );
      for( int i = 0; i < ChannelNames->NumValues() && i < channelsInFile; ++i )
      {
        pItem = new QListWidgetItem( ChannelNames( i ).c_str(), ui->channelList );
        pItem->setFlags( Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
      }
    }
    for( int i = ui->channelList->count() - base; i < channelsInFile; ++i )
    {
      pItem = new QListWidgetItem( QString( tr("Channel %1") ).arg( i + 1 ), ui->channelList );
      pItem->setFlags( Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    }

    int j = 0;
    for( ++j; j < ui->channelList->count()
              && ( ui->channelList->item( j )->flags() & Qt::ItemIsUserCheckable ); ++j )
      ui->channelList->item( j )->setCheckState( Qt::Unchecked );
    for( ++j; j < ui->channelList->count()
              && ( ui->channelList->item( j )->flags() & Qt::ItemIsUserCheckable ); ++j )
      ui->channelList->item( j )->setCheckState( Qt::Checked );
  }
  ui->channelList->blockSignals( false );
}