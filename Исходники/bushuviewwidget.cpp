void BushuViewWidget::slotBushuSelected( QListViewItem *item )
{
    if ( !item )
        return ;

    QString selectedBushuName = item->text( 0 );
    if ( selectedBushuName.isEmpty() )
        return ;

    QFile file( BUSHUDICT );
    if ( file.open( IO_ReadOnly ) )
    {
        QTextStream stream( &file );
        stream.setCodec(QTextCodec::codecForName(BUSHUDICT_ENCODING));
        QString line;

        // search selected bushu line by line
        while ( !stream.atEnd() )
        {
            QStringList chars = QStringList::split( " ",  stream.readLine()  );
            QString bushuName = chars[ 0 ];
            if ( selectedBushuName == bushuName )
            {
                // Display Characters
                chars.remove( bushuName );
                m_charGridView->setCharacters( chars );
            }
        }
        file.close();
    }
}